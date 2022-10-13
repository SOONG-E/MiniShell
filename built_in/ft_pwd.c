#include "minishell.h"

void	ft_pwd(char **arg, int pipe_cnt)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	write(1, pwd, ft_strlen(pwd));
	free(pwd);
	set_exit_code(0);
}
