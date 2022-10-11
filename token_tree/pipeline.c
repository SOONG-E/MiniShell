#include "../include/minishell.h"

void

t_symbol	*sort_redirection(t_symbol *symbol)// cmd < in > out | < in cmd > out
{
	t_symbol	*head;
	t_symbol	*cmd_place;

	head = (t_symbol *)malloc(sizeof(t_symbol));
	head->next = symbol;
	symbol->pre = head;
	while (symbol)
	{
		if (symbol->type == T_CMD
			&& (symbol->next->type == T_PIPE || symbol->next == NULL))
		{
			cmd_place = symbol;
			while (cmd_place->next->type == T_PIPE || cmd_place->next == NULL)
				cmd_place = cmd_place->next;
			swap_place(symbol, cmd_place);
		}
		symbol = symbol->next;
	}
	symbol = head->next;
	free(head);
	return (symbol);
}

t_token	*pipeline(t_symbol *symbol)
{
	t_token	*token;

	if (symbol->type = T_LBRACE)
		return (brace_group(symbol));
	else
	{
		token = make_token(symbol);
		token->left = NULL;
		token->right = NULL;
		token->symbol = sort_redirection(&token->symbol);
		return (token);
	}
}
