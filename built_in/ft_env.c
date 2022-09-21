#include "../include/minishell.h"

void	ft_env(char *env)
{
	t_envlst	*tmp;

	tmp = g_envlst;
	if (env)
		printf("%s\n", getenv(env));
	else
	{
		while (tmp)
		{
			printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}
