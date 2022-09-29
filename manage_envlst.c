#include "./include/minishell.h"

void	ft_envlst_add_back(t_envlst *new)
{
	t_envlst	*tmp;

	tmp = g_envlst;
	if (!tmp)
		g_envlst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_envlst	*ft_envlst_new(char *key, char *value)
{
	t_envlst	*new;

	new = (t_envlst *)malloc(sizeof(t_envlst));
	if (!new)
		exit(0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
