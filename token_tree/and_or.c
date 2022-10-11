#include "../include/minishell.h"

t_token	*and_or(t_symbol *symbol)
{
	t_token		*token;
	t_symbol	*curr;

	curr = get_last_symbol(symbol);
	while (curr)
	{
		if (curr->type == T_OR_IF || curr->type == T_AND_IF)
		{
			token = make_token(curr);
			if (curr->pre)
				curr->pre->next = NULL;
			if (curr->next)
				curr->next->pre = NULL;
			token->left = and_or(symbol);
			token->right = pipeline(curr->next);
			return (token);
		}
		else if (curr->type == T_RBRACE)
			curr = skip_brace(curr->pre);
		curr = curr->pre;
	}
	return (pipeline(symbol));
}