#include "minishell.h"

void	ft_pwd(char **arg, int pipe_cnt)
{
	char	*pwd;

	(void)arg;
	(void)pipe_cnt;
	pwd = getcwd(NULL, 0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	exit(0);
}
