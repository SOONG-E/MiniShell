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
	int		flag;

	pipe(fd_pipe);
	flag = dup_in_redirection(symbol);
	pid = fork();
	if (pid > 0)
	{
		block_signal();
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN);
	}
	else
	{
		close(fd_pipe[0]);
		set_child_signal();
		if (!dup_out_redirection(symbol) && i != pipe_cnt)
			dup2(fd_pipe[1], STDOUT);
		if (flag >= 0)
			execute_cmd(cmd_arr, pipe_cnt);
		else
			exit(errno);
	}
	close(fd_pipe[0]);
	return (pid);
}

int	execute_single_command(t_symbol *symbol, int pipe_cnt)
{
	char	**cmd_arr;
	int		fd_back_up;

	if (!pipe_cnt)
	{
		cmd_arr = make_cmd_arr(symbol);
		if (is_built_in(cmd_arr))
		{
			fd_back_up = dup(STDOUT);
			dup_out_redirection(symbol);
			execute_built_in(cmd_arr, pipe_cnt);
			split_free(cmd_arr);
			dup2(fd_back_up, STDOUT);
			return (1);
		}
		if (cmd_arr)
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
	if (execute_single_command(symbol, pipe_cnt))
		return ;
	pid_lst = (pid_t *)malloc(sizeof(pid_t) * (pipe_cnt + 1));
	if (!pid_lst)
		exit(1);
	i = 0;
	while (symbol)
	{
		cmd_arr = make_cmd_arr(symbol);
		pid_lst[i] = fork_process(symbol, cmd_arr, pipe_cnt, i);
		if (cmd_arr)
			split_free(cmd_arr);
		while (symbol && symbol->type != T_PIPE)
			symbol = symbol->next;
		if (symbol)
			symbol = symbol->next;
		i++;
	}
	wait_process(pid_lst, pipe_cnt + 1);
	dup2(fd_back_up, STDIN);
}
