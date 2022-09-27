#include "../include/minishell.h"

int main()
{
	char *pwd;
	ft_cd("~/Desktop");
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);

	return (0);
}
