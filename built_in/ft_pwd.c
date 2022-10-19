#include "../include/minishell.h"

void	ft_pwd(char **arg, int pipe_cnt)
{
	char	*pwd;

	(void)arg;
	pwd = get_env("PWD");
	if (*pwd)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
		if (pipe_cnt)
			exit(0);
		set_exit_code(0);
	}
	else
	{
		if (pipe_cnt)
			exit(1);
		set_exit_code(1);
	}
}
