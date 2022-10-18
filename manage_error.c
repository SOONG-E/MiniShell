#include "minishell.h"

void	allocat_error(void)
{
	printf("Allocate Error!\n");
	exit(errno);
}

int	error_msg(char *str)
{
	printf("%s: %s\n", SHELL, str);
	set_exit_code(127);
	return (0);
}

void	execute_error(char *cmd)
{
	ft_putstr_fd("minihell: command not found: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(127);
}

void	open_file_error(char *file)
{
	ft_putstr_fd("minihell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(strerror(errno), STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(errno);
}