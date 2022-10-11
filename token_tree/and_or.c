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
			token = make_token(&curr);
			printf("curr = %s\n", token->symbol->str);/////test
			if (curr->pre)
				curr->pre->next = NULL;
			if (curr->next)
				curr->next->pre = NULL;
			token->left = and_or(symbol);
			printf("left = %s\n", token->left->symbol->str);
			printf("before right = %s\n", curr->next->next->str);
			token->right = pipeline(curr->next);
			printf("after right = %s\n", token->right->symbol->str);
			curr->pre = NULL;
			curr->next = NULL;
			return (token);
		}
		else if (curr->type == T_RBRACE)
			curr = skip_brace(curr->pre);
		if (curr)
			curr = curr->pre;
	}
	return (pipeline(symbol));
}