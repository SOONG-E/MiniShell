#include "./include/minishell.h"

static int	count_until_pipe(t_symbol *symbol)
{
	int	count;

	count = 0;
	while (symbol && symbol->type != T_PIPE)
	{
		symbol = symbol->next;
		++count;
	}
	return (count);
}

static char	**make_cmd_arr(t_symbol *symbol)
{
	int		idx;
	int 	count;
	char	**ret;

	count = count_until_pipe(symbol);
	ret = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!ret)
		allocat_error();
	idx = 0;
	while (idx < count)
	{
		ret[idx] = ft_strdup(symbol->str);
		symbol = symbol->next;
		++idx;
	}
	return (ret);
}

int	excute_built_in(char **cmd_arr, int pipe_cnt)
{
	if (!ft_strcmp("cd", cmd_arr[0]))
		ft_cd(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("echo", cmd_arr[0]))
		ft_echo(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("env", cmd_arr[0]))
		ft_env(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("exit", cmd_arr[0]))
		ft_exit(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("export", cmd_arr[0]))
		ft_export(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("pwd", cmd_arr[0]))
		ft_pwd(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("unset", cmd_arr[0]))
		ft_unset(cmd_arr, pipe_cnt);
	else
		return (0);
}

void	excute_cmd(char	**cmd_arr, int pipe_cnt)
{
	char	*cmd_path;
	
	cmd_path = get_cmd_path(cmd_arr[0]);

	if (!cmd_path)
		error_allocate();
	if (excute_built_in(cmd_arr))
		execve(cmd_path, cmd_arr, char **env);
	error_excute_cmd(cmd_arr[0]);
}

pid_t	fork_process(t_symbol *symbol, char *cmd_arr, int pipe_cnt)
{
	pid_t	pid;
	int		fd_pipe[2];

	pipe(fd_pipe);
	pid = fork();
	if (pid > 0)
	{
		close(fd_pipe[1]);
		if (!dup_in_redirection(symbol, fd_pipe))
			dup2(fd_pipe[0], STDIN);
		waitpid(pid, NULL, WNOHANG);
	}
	else
	{
		close(fd_pipe[0]);
		if (!dup_out_redirection(symbol, fd_pipe))
			dup2(fd_pipe[1], STDOUT);
		excute_cmd(cmd_arr, pipe_cnt);
	}
	return (pid);
}

void	excute_pipe_line(t_symbol *symbol)
{
	pid_t	*pid_lst;
	int		pipe_cnt;
	int		i;
	char	**cmd_arr;

	i = 0;
	pipe_cnt = get_pipe_cnt(symbol);
	if (!pipe_cnt == builtin)
	pid_lst = (pid_t *)malloc(sizeof(pid_t) * pipe_cnt);
	while(symbol)
	{
		cmd_arr = make_cmd_arr(symbol);
		pid_lst[i] = fork_process(symbol, cmd_arr, pipe_cnt);
		while (symbol && symbol->type != T_PIPE)
			symbol = symbol->next;
		if (symbol)
			symbol = symbol->next;
		i++;
	}
}
