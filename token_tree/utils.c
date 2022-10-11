#include "../include/minishell.h"

t_symbol	*skip_brace(t_symbol *symbol)
{
	int	cnt;

	cnt = 1;
	while (1)
	{
		if (symbol->type == T_LBRACE)
			cnt--;
		else if (symbol->type == T_RBRACE)
			cnt++;
		if (cnt == 0)
			return (symbol);
		symbol = symbol->pre;
	}
	return (symbol);
}
