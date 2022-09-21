#include "../include/minishell.h"

void	ft_unset(char *rmvkey)
{
	t_envlst	*tmp;
	t_envlst	*curr;
	t_envlst	*next;

	if (!ft_strcmp(g_envlst->key, rmvkey))
	{
		next = g_envlst->next;
		ft_del_lst(g_envlst);
		g_envlst = next;
	}
	tmp = g_envlst;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->key, rmvkey))
		{
			next = g_envlst->next;
			ft_del_lst(g_envlst);
			g_envlst = next;
		}
		tmp = tmp->next;
	}
}