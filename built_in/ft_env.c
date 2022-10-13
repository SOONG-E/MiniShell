#include "minishell.h"

void	ft_env(char *arg)
{
	t_envlst	*tmp;

	tmp = g_info->envlst;
	if (arg)
	{
		printf("env: %s: No such file or directory\n", arg);
		set_exit_code(127);
	}
	else
	{
		while (tmp)
		{
			printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		set_exit_code(0);
	}
}
