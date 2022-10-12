#include "../include/minishell.h"

t_token	*brace_group(t_symbol *symbol)
{
	t_symbol *temp;

	symbol = symbol->next;
	//free_symbol(symbol->pre);
	if (symbol->pre)
		symbol->pre->next = NULL;
	symbol->pre = NULL;
	temp = get_last_symbol(symbol);
	temp = temp->pre;
	if (temp->next)
		temp->next->pre = NULL;
	temp->next = NULL;
	//free_symbol(temp);
	return (and_or(symbol));
}
