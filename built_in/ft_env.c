#include "minishell.h"

void	ft_env(char **arg, int pipe_cnt)
{
	t_envlst	*tmp;

	(void)pipe_cnt;
	tmp = g_info->envlst;
	if (arg)
	{
		printf("env: %s: No such file or directory\n", arg);
		exit(127);
	}
	else
	{
		while (tmp)
		{
			if (tmp->value)
			{
				write(1, tmp->key, ft_strlen(tmp->key));
				write(1, "=", 1);
				write(1, tmp->value, ft_strlen(tmp->value));
				write(1, "\n", 1);
			}
			tmp = tmp->next;
		}
		exit(0);
	}
}
