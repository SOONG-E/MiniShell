#include "../include/minishell.h"

t_token	*brace_group(t_symbol *symbol)
{
	t_symbol *temp;

	symbol = symbol->next;
	//free_symbol(symbol->pre);
	temp = get_last_symbol(symbol);
	if (temp->next)
		temp->next->pre = NULL;
	//free_symbol(temp);
	return (and_or(symbol));
}
