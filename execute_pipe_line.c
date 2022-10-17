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

	while (symbol->next != NULL && symbol->next->type != T_PIPE
		&& symbol->type != T_CMD)
		symbol = symbol->next;
	if (symbol->type != T_CMD)
		return (NULL);
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

int	is_built_in(char **cmd_arr)
{
	if (!cmd_arr)
		return (0);
	if (!ft_strcmp("cd", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("echo", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("env", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("exit", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("export", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd_arr[0]))
		return (1);
	else
		return (0);
}

int	execute_built_in(char **cmd_arr, int pipe_cnt)
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
		return (1);
	return (0);
}

void	execute_cmd(char **cmd_arr, int pipe_cnt)
{
	char	*path;
	char	*cmd_path;
	char	**env;

	if (!cmd_arr)
		exit(0);
	path = get_env("PATH");
	cmd_path = get_cmd_path(cmd_arr[0], path);
	free(path);
	env = make_env();
	if (execute_built_in(cmd_arr, pipe_cnt))
		execve(cmd_path, cmd_arr, env);
	split_free(env);
	execute_error(cmd_arr[0]);
}

pid_t	fork_process(t_symbol *symbol, char **cmd_arr, int pipe_cnt, int i)
{
	pid_t	pid;
	int		fd_pipe[2];

	pipe(fd_pipe);
	pid = fork();
	if (pid > 0)
	{
		block_signal();
		close(fd_pipe[1]);
		if (!dup_in_redirection(symbol) && i != 0)
			dup2(fd_pipe[0], STDIN);
	}
	else
	{
		close(fd_pipe[0]);
		set_child_signal();
		if (!dup_out_redirection(symbol) && i < pipe_cnt)
			dup2(fd_pipe[1], STDOUT);
		execute_cmd(cmd_arr, pipe_cnt);
	}
	return (pid);
}

void	wait_last_process(pid_t last_pid)
{
	int	exit_code;

	waitpid(last_pid, &exit_code, 0);
	set_exit_code(get_exitcode(exit_code));
}

void	execute_pipe_line(t_symbol *symbol)
{
	pid_t	*pid_lst;
	int		pipe_cnt;
	int		i;
	int		fd_back_up;
	char	**cmd_arr;

	fd_back_up = dup(STDIN);
	pipe_cnt = get_pipe_cnt(symbol);
	dup_in_redirection(symbol);
	cmd_arr = make_cmd_arr(symbol);
	if (!pipe_cnt)
	{
		cmd_arr = make_cmd_arr(symbol);
		if (is_built_in(cmd_arr))
		{
			execute_built_in(cmd_arr, pipe_cnt);
			return ;//??
		}
		split_free(cmd_arr);
	}
	pid_lst = (pid_t *)malloc(sizeof(pid_t) * pipe_cnt);
	i = 0;
	while(symbol) 
	{
		cmd_arr = make_cmd_arr(symbol);
		pid_lst[i] = fork_process(symbol, cmd_arr, pipe_cnt, i);
		split_free(cmd_arr);
		while (symbol && symbol->type != T_PIPE)
			symbol = symbol->next;
		if (symbol)
			symbol = symbol->next;
		i++;
	}
	wait_last_process(pid_lst[i - 1]);
	dup2(fd_back_up, STDIN);
}
