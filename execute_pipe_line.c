#include "./include/minishell.h"

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
		if (i != 0)
			dup2(fd_pipe[0], STDIN);
	}
	else
	{
		close(fd_pipe[0]);
		set_child_signal();
		dup_in_redirection(symbol);
		if (!dup_out_redirection(symbol) && i < pipe_cnt)
			dup2(fd_pipe[1], STDOUT);
		execute_cmd(cmd_arr, pipe_cnt);
	}
	return (pid);
}

int	execute_single_commend(t_symbol *symbol, int pipe_cnt)
{
	char	**cmd_arr;

	dup_in_redirection(symbol);
	if (!pipe_cnt)
	{
		cmd_arr = make_cmd_arr(symbol);
		if (is_built_in(cmd_arr))
		{
			execute_built_in(cmd_arr, pipe_cnt);
			split_free(cmd_arr);
			return (1);
		}
		split_free(cmd_arr);
	}
	return (0);
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
	if (execute_single_commend(symbol, pipe_cnt))
		return ;
	pid_lst = (pid_t *)malloc(sizeof(pid_t) * pipe_cnt);
	i = 0;
	while (symbol)
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
	wait_process(pid_lst, pipe_cnt);
	dup2(fd_back_up, STDIN);
}