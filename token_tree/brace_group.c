#include "../include/minishell.h"

t_token	*brace_group(t_symbol *symbol)
{
	t_token	*token;
	t_symbol *temp;

	symbol = symbol->next;
	free_symbol(symbol->pre);
	temp = ft_get_last_symbol(symbol);
	free_symbol(temp);
	return (and_or(symbol));
}
