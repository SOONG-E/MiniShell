#include "./include/minishell.h"

int	get_exitcode(int status)
{
	return (status >> 8 & 0x000000ff);
}

int	get_pipe_cnt(t_symbol *symbol)
{
	int	cnt;
	
	cnt = 0;
	while (symbol)
	{
		if (symbol->type == T_PIPE)
			cnt++;
		symbol = symbol->next;
	}
	return (cnt);
}

void	read_here_doc(char *limiter, int fd[2])
{
	size_t	len_limiter;
	char	*line;
	int		status;

	len_limiter = ft_strlen(limiter);
	while (1)
	{
		status = get_next_line(STDIN, &line);
		if (status == 0)
			close_all_pipefd(fd, 0);
		else if (status == -1)
			close_all_pipefd(fd, 1);
		if (line[len_limiter] == '\n'
			&& limiter && !ft_strncmp(line, limiter, len_limiter))
			close_all_pipefd(fd, 0);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

int	open_file(char *file, int redirection_type)
{
	int	fd;

	if (redirection_type == T_IN_RID)
		fd = open(file, O_RDONLY);
	else if (redirection_type == T_OUT_RID)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (redirection_type == T_OUT_HEREDOC)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
		ft_putstr_fd(strerror(errno), STDERR);
	return (fd);
}

t_symbol	*dup_in_redirection(t_symbol *symbol, int *fd)
{
	int	fd_redirection;
	int	flag;

	fd_redirection = STDIN;
	flag = 0;
	while (symbol->type != T_CMD)
	{
		if (symbol->type ==  T_IN_RID)
		{
			fd_redirection = open_file(symbol->next->str, T_IN_RID);
			dup2(fd_redirection, fd[0]);
			flag = 1;
		}
		else if (symbol->type == T_IN_HEREDOC)
			read_here_doc(symbol->next->str, fd);
		if (fd_redirection < 0)
		{
			set_exit_code(errno);
			return (NULL);
		}
		symbol = symbol->next->next;
	}
	return (flag);
}

t_symbol	*dup_out_redirection(t_symbol *symbol, int *fd)
{
	t_symbol	*rid_symbol;
	int			fd_redirection;
	int			flag;

	fd_redirection = STDIN;
	flag = 0;

	while (symbol->type != T_CMD)
	{
		
	}
	while (symbol->type != T_CMD)
	{
		if (flag)
			close(fd_redirection);
		if (symbol->type ==  T_OUT_RID)
		{
			fd_redirection = open_file(symbol->next->str, T_OUT_RID);
			dup2(fd_redirection, fd[1]);
			flag = 1;
		}
		else if (symbol->type == T_OUT_HEREDOC)
		{
			fd_redirection = open_file(symbol->next->str, T_OUT_HEREDOC);
			dup2(fd_redirection, fd[1]);
			flag = 1;
		}
		if (fd_redirection < 0)
		{
			set_exit_code(errno);
			return (NULL);
		}
		symbol = symbol->next->next;
	}
	return (flag);
}
