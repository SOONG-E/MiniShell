#include "./include/minishell.h"

void	allocat_error(void)
{
	printf("Allocate Error!\n");// error 디테일 추가 필요!!
	exit(1);
}

int	error_msg(char *str)
{
	printf("%s: %s\n", SHELL, str);
	return (0);
}
