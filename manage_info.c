#include "./include/minishell.h"

void	init_info(char **env)
{
	g_info = (t_info *)malloc(sizeof(t_info));
	g_info->envlst = NULL;
	parsing_env(env);
	g_info->exit_code = ft_itoa(0);
}

void	set_exit_code(int code)
{
	free(g_info->exit_code);
	g_info->exit_code = ft_itoa(code);
}