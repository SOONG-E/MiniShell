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

int	classify_type(t_symbol	*symbol)
{
	int	op;

	op = classify_op(symbol->str);
	if (op)
	{
		if (op == T_RBRACE)
			return (op);
		else if (symbol->next && classify_op(symbol->next->str) > 0)
			return (op);
		else if (symbol->next)
			symbol->next->type = (T_CMD + (op == T_IN_RID || op == T_OUT_RID));
		return (op);
	}
	else if (!ft_strcmp(symbol->str, "-n"))
	{
		if (symbol->pre
			&& (symbol->pre->type == T_CMD || symbol->pre->type == T_OPTION))
			return (T_OPTION);
	}
	else
		return (T_ARG);
	return (T_ARG);
} //-n아닌경우 무조건 arg !  누가 뭐라하면 민수칸님이 패기로함;;

void	symbolizing(t_symbol *symbol_lst)
{
	t_symbol	*temp;

	temp = symbol_lst;
	if (!classify_op(temp->str))
	{
		temp->type = T_CMD;
		symbol_lst = symbol_lst->next;
	}
	while (temp)
	{
		if (temp->type < 0)
			temp->type = classify_type(temp);
		temp = temp->next;
	}
	// //test
	// for (int i = 0; symbol_lst[i].str ; ++i)
	// 	printf("%s type = %d\n", symbol_lst[i].str, symbol_lst[i].type);
	// //
}
