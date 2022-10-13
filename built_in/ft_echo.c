#include "minishell.h"

void	ft_echo(char **arg, int pipe_cnt)
{
	int	idx;
	int new_line;

	new_line = 1;
	idx = 1;
	while (arg[idx] && !ft_strcmp(arg[idx], "-n"))
		++idx;
	if (idx == 1)
		new_line = 0;
	while (arg[idx])
	{
		write(1, arg[idx], ft_strlen(arg[idx]));
		++idx;
		if (arg[idx])
			write(1, " ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
	set_exit_code(0);
}
