#include "../include/minishell.h"

t_token	*and_or(t_symbol *symbol)
{
	t_token		*token;
	t_symbol	*curr;

	curr = ft_get_last_symbol(symbol);
	while (curr)
	{
		if (curr->type == T_OR_IF || curr->type == T_AND_IF)
		{
			token = make_token(curr);
			curr->pre->next = NULL;
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