#include "../include/minishell.h"

void	ft_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}