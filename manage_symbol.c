#include "./include/minishell.h"

t_symbol	*ft_symbol_new(char	*str)
{
	t_symbol	*new;

	new = (t_symbol *)malloc(sizeof(t_symbol));
	if (!new)
		exit(1);
	new->str = ft_strdup(str);
	new->type = -1;
	new->pre = NULL;
	new->next = NULL;
	free(str);
	return (new);
}

void	lst_symbol_add_back(t_symbol **head, t_symbol *new)
{
	t_symbol	*tmp;

	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->pre = tmp;
	}
}

t_symbol	*make_symbol_lst(char **temp)
{
	t_symbol	*symbol_lst;
	t_symbol	*new;
	int			i;

	symbol_lst = NULL;
	i = 0;
	while (temp[i])
	{
		new = ft_symbol_new(temp[i]);
		lst_symbol_add_back(&symbol_lst, new);
		i++;
	}
	free(temp);
	return (symbol_lst);
}

t_symbol	*lst_symbol_add_middle(t_symbol *symbol, t_symbol *new)
{
	t_symbol	*new_end;

	new_end = new;
	while (new_end->next)
		new_end = new_end->next;
	symbol->pre->next = new;
	new->pre = symbol->pre;
	if (symbol->next)
		lst_symbol_add_back(&new, symbol->next);
	free(symbol->str);
	free(symbol);
	return (new_end);
}
