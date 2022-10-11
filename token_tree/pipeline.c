#include "../include/minishell.h"

void	swap_place(t_symbol *symbol, t_symbol *cmd_place)
{
	symbol->pre->next = symbol->next;
	symbol->next->pre = symbol->pre;

	if (cmd_place->next)
	{
		cmd_place->next->pre = symbol;
		symbol->next = cmd_place->next;
	}
	else
		symbol->next = NULL;
	cmd_place->next = symbol;
	symbol->pre = cmd_place;
}

t_symbol	*sort_redirection(t_symbol *symbol)// | cmd < in > out | < in cmd > out
{
	t_symbol	*head;
	t_symbol	*cmd_place;

	head = (t_symbol *)malloc(sizeof(t_symbol));
	head->next = symbol;
	symbol->pre = head;
	while (symbol)
	{
		if (symbol->type != T_CMD
			&& (symbol->next->type != T_PIPE || symbol->next != NULL))
		{
			cmd_place = symbol;
			while (cmd_place->next->type == T_PIPE || cmd_place->next == NULL)
				cmd_place = cmd_place->next;
			swap_place(symbol, cmd_place);
		}
		symbol = symbol->next;
	}
	symbol = head->next;
	symbol->pre = NULL;
	free(head);
	return (symbol);
}

t_token	*pipeline(t_symbol *symbol)
{
	t_token	*token;

	if (!symbol)
		return (NULL);
	if (symbol->type == T_LBRACE)
		return (brace_group(symbol));
	else
	{
		token = make_token(&symbol);
		//-------------------------------
		t_symbol *tmp;
		tmp = token->symbol;
		while (tmp)
		{
			
			tmp = tmp->next;
		}
		//------------------------------
		//token->symbol = sort_redirection(token->symbol);
		return (token);
	}
}
