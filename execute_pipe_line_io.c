#include "./include/minishell.h"

void	close_all_pipefd(int *fd, int error_case)
{
	close(fd[0]);
	close(fd[1]);
	if (error_case == 1)
		ft_putstr_fd("pipex: Here_doc allocate error!\n", STDERR);
	exit(error_case);
}

int	open_file(char *file, int redirection_type)
{
	int	fd;

	fd = 0;
	if (redirection_type == T_IN_RID)
		fd = open(file, O_RDONLY);
	else if (redirection_type == T_OUT_RID)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (redirection_type == T_IN_HEREDOC)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_SYNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (redirection_type == T_OUT_HEREDOC)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
		ft_putstr_fd(strerror(errno), STDERR);
	return (fd);
}

void	read_here_doc(char *limiter)
{
	size_t	len_limiter;
	char	*line;
	int		status;
	int		fd;

	fd = open_file(".heredoc_tmp", T_IN_HEREDOC);
	len_limiter = ft_strlen(limiter);
	while (1)
	{
		status = get_next_line(STDIN, &line);
		if (status == 0)
			break ;
		else if (status == -1)
			allocat_error();
		if (line[len_limiter] == '\n'
			&& limiter && !ft_strncmp(line, limiter, len_limiter))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}

int	dup_in_redirection(t_symbol *symbol)
{
	int	fd_redirection;
	int	flag;

	fd_redirection = STDIN;
	flag = 0;
	while (symbol->type != T_CMD)
	{
		if (symbol->type == T_IN_RID)
		{
			if (fd_redirection != STDIN)
				close(fd_redirection);
			fd_redirection = open_file(symbol->next->str, T_IN_RID);
			dup2(fd_redirection, STDIN);
			flag = 1;
		}
		else if (symbol->type == T_IN_HEREDOC)
		{
			if (fd_redirection != STDIN)
				close(fd_redirection);
			read_here_doc(symbol->next->str);
			fd_redirection = open_file(".heredoc_tmp", T_IN_RID);
			dup2(fd_redirection, STDIN);
			flag = 1;
		}
		if (fd_redirection < 0)
		{
			set_exit_code(errno);
			exit(errno);
		}
		symbol = symbol->next->next;
	}
	return (flag);
}

int	dup_out_redirection(t_symbol *symbol)
{
	int			type_redirection;
	int			fd_redirection;
	int			flag;

	fd_redirection = STDOUT;
	flag = 0;
	while (symbol->type != T_CMD)
	{
		type_redirection = symbol->type;
		if (symbol->type == T_OUT_RID || symbol->type == T_OUT_HEREDOC)
		{
			if (fd_redirection != STDOUT)
				close(fd_redirection);
			fd_redirection = open_file(symbol->next->str, type_redirection);
			dup2(fd_redirection, STDOUT);
			flag = 1;
		}
		if (fd_redirection < 0)
		{
			set_exit_code(errno);
			exit(errno);
		}
		symbol = symbol->next->next;
	}
	return (flag);
}
