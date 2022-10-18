#include "minishell.h"

int	classify_op(char *str)
{
	if (ft_strlen(str) != 1 || str[0] > 0)
		return (-1);
	if (str[0] == OP_PIPE)
		return (T_PIPE);
	else if (str[0] == OP_OR_IF)
		return (T_OR_IF);
	else if (str[0] == OP_AND_IF)
		return (T_AND_IF);
	else if (str[0] == OP_IN_HEREDOC)
		return (T_IN_HEREDOC);
	else if (str[0] == OP_OUT_HEREDOC)
		return (T_OUT_HEREDOC);
	else if (str[0] == OP_LBRACE)
		return (T_LBRACE);
	else if (str[0] == OP_RBRACE)
		return (T_RBRACE);
	else if (str[0] == OP_IN_RID)
		return (T_IN_RID);
	else if (str[0] == OP_OUT_RID)
		return (T_OUT_RID);
	else
		return (-1);
}

t_symbol	*find_first_cmd(t_symbol *symbol)
{
	while (symbol && (symbol->type == T_FILEPATH
			|| (T_IN_RID <= symbol->type && symbol->type <= T_OUT_HEREDOC)))
		symbol = symbol->next;
	if (symbol)
		symbol->type = T_CMD;
	return (symbol->next);
}

t_symbol	*classify_type(t_symbol *symbol)
{
	symbol = find_first_cmd(symbol);
	while (symbol && symbol->type != T_PIPE && !ft_strcmp(symbol->str, "-n"))
	{
		if (symbol->type < 0)
			symbol->type = T_OPTION;
		symbol = symbol->next;
	}
	while (symbol && symbol->type != T_PIPE)
	{
		if (symbol->type < 0)
			symbol->type = T_ARG;
		symbol = symbol->next;
	}
	return (symbol);
}

void	find_op(t_symbol *symbol_lst)
{
	t_symbol	*temp;

	temp = symbol_lst;
	while (temp)
	{
		if (temp->type < 0)
		{
			temp->type = classify_op(temp->str);
			if (temp->next
				&& (T_IN_RID <= temp->type && temp->type <= T_OUT_HEREDOC))
			{
				if (classify_op(temp->next->str) < 0)
					temp->next->type = T_FILEPATH;
			}
		}
		temp = temp->next;
	}
}

void	symbolizing(t_symbol *symbol_lst)
{
	t_symbol	*temp;

	find_op(symbol_lst);
	temp = symbol_lst;
	while (temp)
	{
		if (temp->type < 0)
			temp = classify_type(temp);
		if (temp)
			temp = temp->next;
	}
}
