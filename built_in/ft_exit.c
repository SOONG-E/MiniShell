#include "../include/minishell.h"

void	ft_exit(char **arg, int pipe_cnt)
{
	(void)pipe_cnt;
	if (arg[1])
	{
		if (arg[2])
			exit(1);
		else
			exit(ft_atoi(arg[1]));
	}
	else
		exit(0);
}
