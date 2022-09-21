#include "../include/minishell.h"

void	ft_echo(char *arg, int option)
{
	write(1, arg, ft_strlen(arg));
	if (option)
		return ;
	else
		write(1, "\n", 1);
}
