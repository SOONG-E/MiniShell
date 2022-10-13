#include "minishell.h"

t_symbol	*skip_brace(t_symbol *symbol)
{
	int	cnt;

	cnt = 1;
	while (symbol)
	{
		if (symbol->type == T_LBRACE)
			cnt--;
		else if (symbol->type == T_RBRACE)
			cnt++;
		if (cnt == 0)
			break ;
		symbol = symbol->pre;
	}
	return (symbol);
}
