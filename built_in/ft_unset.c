#include "../include/minishell.h"

void	ft_unset(char *rmvkey)
{
	t_envlst	*tmp;
	t_envlst	*next;

	if (!ft_strcmp(g_envlst->key, rmvkey))
	{
		next = g_envlst->next;
		free(g_envlst);
		g_envlst = next;
	}
	tmp = g_envlst;
	while (g_envlst->next)
	{
		if (!ft_strcmp(g_envlst->next->key, rmvkey))
		{
			next = tmp->next;
			free(g_envlst);
			g_envlst = next;
		}
		g_envlst = g_envlst->next;
	}
	g_envlst = tmp;
}
