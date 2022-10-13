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

pid_t	fork_process(t_symbol *symbol)
{
	pid_t	pid;
	int		fd_pipe[2];
	char	**cmd_arr;

	cmd_arr = make_cmd_arr(symbol);
	pipe(fd_pipe);
	pid = fork();
	if (pid > 0)
	{
		close(fd_pipe[1]);
		if (dup_in_redirection(symbol, fd_pipe))
			dup2(fd_pipe[0], STDIN);
		waitpid(pid, NULL, WNOHANG);
	}
	else
	{
		close(fd_pipe[0]);
		if (dup_out_redirection(symbol, fd_pipe))
			dup2(fd_pipe[1], STDOUT);
		excute_cmd(cmd_arr);
	}
	return (pid);
}

void	excute_pipe_line(t_symbol *symbol)
{
	int	*pid_lst;
	int pipe_cnt;
	int	i;

	i = 0;
	pipe_cnt = get_pipe_cnt(symbol);
	pid_lst = (int *)malloc(sizeof(pid_lst) * pipe_cnt);
	while(symbol)
	{
		pid_lst[i] = fork_process(symbol);
		while (symbol && symbol->type != T_PIPE)
			symbol = symbol->next;
		if (symbol)
			symbol = symbol->next;
		i++;
	}
	waitpid()
}
