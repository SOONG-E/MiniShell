#include "./include/minishell.h"

int	classify_op(char *str)
{
	if (ft_strlen(str) != 1 || str[0] > 0)
		return (0);
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
		return (0);
}

t_symbol	*classify_type(t_symbol	*symbol)
{
	symbol->type = T_CMD;
	symbol = symbol->next;
	while (symbol && symbol->type < 0 && !ft_strcmp(symbol->str, "-n"))
	{
		symbol->type = T_OPTION;
		symbol = symbol->next;
	}
	while (symbol && symbol->type < 0)
	{
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
			if (!temp->type)
				temp->type = -1;
			else if (temp->next && (T_IN_RID <= temp->type && temp->type <= T_OUT_HEREDOC))
			{
				if (!classify_op(temp->next->str))
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
	//test
	// while (symbol_lst)
	// {
	// 	char *type;
	// 	switch (symbol_lst->type)
	// 	{
	// 	case 0:
	// 		type = "CMD";
	// 		break;
	// 	case 1:
	// 		type = "FILEPATH";
	// 		break;
	// 	case 2:			
	// 		type = "OPTION";
	// 		break;
	// 	case 3:			
	// 		type = "ARG";
	// 		break;
	// 	case 4:			
	// 		type = "PIPE";
	// 		break;
	// 	case 5:			
	// 		type = "AND_IF";
	// 		break;
	// 	case 6:			
	// 		type = "OR_IF";
	// 		break;
	// 	case 7:			
	// 		type = "LBRACE";
	// 		break;
	// 	case 8:			
	// 		type = "RBRACE";
	// 		break;
	// 	case 9:			
	// 		type = "IN_RID";
	// 		break;
	// 	case 10:			
	// 		type = "OUT_RID";
	// 		break;
	// 	case 11:			
	// 		type = "IN_HEREDOC";
	// 		break;
	// 	case 12:			
	// 		type = "OUT_HEREDOC";
	// 		break;
	// 	}
	// 	printf("%s \ttype = %s\n", symbol_lst->str, type);
	// 	symbol_lst = symbol_lst->next;
	// }
	//
}
