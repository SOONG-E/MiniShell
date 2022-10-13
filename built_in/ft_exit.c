#include "minishell.h"

void	ft_exit(char **arg, int pipe_cnt)
{
	int	(*f_exit)(int);

	if (pipe_cnt)
		f_exit = set_exit_code;
	else
		f_exit = exit;
	if (arg[1])
	{
		if (arg[2])
			f_exit(1);
		else
			f_exit(ft_atoi(arg[1]));
	}
	else
		f_exit(0);
}
