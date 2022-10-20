#include "minishell.h"

char	*get_origin_op(int type)
{
	if (type == T_PIPE)
		return ("|");
	else if (type == T_AND_IF)
		return ("&&");
	else if (type == T_OR_IF)
		return ("||");
	else if (type == T_LBRACE)
		return ("(");
	else if (type == T_RBRACE)
		return (")");
	else if (T_IN_RID <= type && type <= T_OUT_HEREDOC)
		return ("newline");
	return (0);
}

int	syntax_error_token(char *str)
{
	if (str[0] < 0)
		str = get_origin_op(classify_op(str));
	printf("%s: syntax error near unexpected token \'%s\'\n", SHELL, str);
	set_exit_code(127);
	return (1);
}

int	check_expression_error(t_symbol *symbol)
{
	int	lbrace_in_row;
	int	rbrace_in_row;

	lbrace_in_row = 0;
	rbrace_in_row = 0;
	if (symbol->type == T_LBRACE)
		++lbrace_in_row;
	symbol = symbol->next;
	while (symbol)
	{
		if (symbol->pre->type != T_LBRACE && symbol->type == T_LBRACE)
			lbrace_in_row = 1;
		else if (symbol->type == T_LBRACE)
			++lbrace_in_row;
		else if (symbol->pre->type != T_RBRACE && symbol->type == T_RBRACE)
			rbrace_in_row = 1;
		else if (symbol->type == T_RBRACE)
			++rbrace_in_row;
		else
			rbrace_in_row = 0;
		if (lbrace_in_row > 1 && rbrace_in_row > 1)
			return (1);
		symbol = symbol->next;
	}
	return (0);
}

int	check_unexpected_token(t_symbol *symbol_lst)
{
	if (symbol_lst->type >= 1 && symbol_lst->type <= 6)
		return (syntax_error_token(get_origin_op(symbol_lst->type)));
	while (symbol_lst->next)
	{
		if (symbol_lst->type == T_LBRACE)
			return (lbrace_case(symbol_lst));
		else if (symbol_lst->type == T_RBRACE)
			return (rbrace_case(symbol_lst));
		else if (symbol_lst->type >= T_PIPE && symbol_lst->type <= T_OR_IF)
			return (pipe_andif_orif_case(symbol_lst));
		else if (symbol_lst->type >= T_IN_RID && \
		symbol_lst->type <= T_OUT_HEREDOC)
			return (direction_case(symbol_lst));
		symbol_lst = symbol_lst->next;
	}
	if (symbol_lst->pre && symbol_lst->pre->type == \
	T_RBRACE && symbol_lst->type != T_RBRACE)
		return (syntax_error_token(symbol_lst->str));
	if (symbol_lst->type >= T_PIPE && symbol_lst->type != T_RBRACE)
		return (syntax_error_token(get_origin_op(symbol_lst->type)));
	return (0);
}

int	validate(t_symbol *symbol_lst)
{
	if (check_unexpected_token(symbol_lst))
		return (1);
	if (check_expression_error(symbol_lst))
	{
		error_msg("syntax error in expression");
		return (1);
	}
	return (0);
}

/*
validate rule

1. lbrace
 1-1. pre가 ||, && 아닌 경우	syntax_error_token("(")
 1-2. next가 연산자인 경우(< << > >> 제외)		syntax_error_token(연산자)
2. rbrace
 2-1. next가 연산자가 아닌 경우, lbrace인 경우	syntax_error_token(next->type)
3. 

*/
