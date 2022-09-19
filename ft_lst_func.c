#include "./include/minishell.h"

void	ft_lst_add_back(t_envlst *new)
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

t_envlst	*ft_lst_new(char *key, char *value)
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

void    printf_lst(void)
{
    t_envlst	*temp;

	temp = g_envlst;
	while (temp)
	{
		printf("KEY: %s\nVALUE: %s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
