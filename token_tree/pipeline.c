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

t_symbol	*find_cmd_place(t_symbol *symbol)
{
	t_symbol	*cmd_place;

	cmd_place = symbol;
	while (1)
	{
		if (!cmd_place->next)
			break ;
		if (cmd_place->next->type == T_PIPE)
			break ;
		cmd_place = cmd_place->next;
	}
	return (cmd_place);
}

t_symbol	*sort_redirection(t_symbol *symbol)
{
	t_symbol	*head;
	t_symbol	*cmd_place;

	head = (t_symbol *)malloc(sizeof(t_symbol));
	head->next = symbol;
	symbol->pre = head;
	while (symbol->next)
	{	
		if (symbol->type == T_CMD)
		{
			cmd_place = find_cmd_place(symbol);
			if (symbol != cmd_place)
				swap_place(symbol, cmd_place);
		}
		if (symbol->next)
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
		token = make_token(symbol);
		//token->symbol = sort_redirection(token->symbol);
		return (token);
	}
}
