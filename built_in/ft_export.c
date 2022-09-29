#include "../include/minishell.h"

void	ft_export(char *key, char *value)
{
	t_envlst	*tmp;

	tmp = g_envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	ft_envlst_add_back(ft_envlst_new(key, value));
}
