#include "../include/minishell.h"

static void	ft_refresh_env(void); //prototype

static void	ft_refresh_env(void)
{
	t_envlst	*tmp;

	tmp = g_envlst;
	while (tmp)
	{
		tmp->value = getenv(tmp->key);
		tmp = tmp->next;
	}
}