#include "./include/minishell.h"

int	lbrace_case(t_symbol *symbol_lst)
{
	if (symbol_lst->pre && !(T_PIPE <= symbol_lst->pre->type \
	&& symbol_lst->pre->type <= T_LBRACE))
		return (syntax_error_token("("));
	if (symbol_lst->next->type >= T_PIPE && symbol_lst->next->type != T_LBRACE)
		return (syntax_error_token(get_origin_op(symbol_lst->next->type)));
	return (0);
}

int	rbrace_case(t_symbol *symbol_lst)
{
	if (symbol_lst->next->type < T_PIPE || symbol_lst->next->type == T_LBRACE)
		return (syntax_error_token(symbol_lst->next->str));
	return (0);
}

int	pipe_andif_orif_case(t_symbol *symbol_lst)
{
	if (symbol_lst->next->type >= T_PIPE && \
	symbol_lst->next->type <= T_OR_IF && \
	symbol_lst->next->type != T_LBRACE)
		return (syntax_error_token(get_origin_op(symbol_lst->next->type)));
	return (0);
}

int	direction_case(t_symbol *symbol_lst)
{
	if (symbol_lst->next->type != T_FILEPATH)
		return (syntax_error_token(get_origin_op(symbol_lst->next->type)));
	return (0);
}
