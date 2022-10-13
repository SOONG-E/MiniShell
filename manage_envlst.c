#include "minishell.h"

void	ft_envlst_add_back(t_envlst *new)
{
	t_envlst	*tmp;

	tmp = g_info->envlst;
	if (!tmp)
		g_info->envlst = new;
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
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_envlst	*get_envlst(char *key)
{
	t_envlst	*temp;

	temp = g_info->envlst;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	set_envlst(char *key, char *value)
{
	t_envlst	*envlst;

	envlst = get_envlst(key);
	if (!envlst)
		ft_envlst_add_back(ft_envlst_new(key, value));
	else
	{
		free(envlst->value);
		envlst->value = value;
	}
}
