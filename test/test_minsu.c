#include "../include/minishell.h"

char	*get_value_n(char *key, int n)
{
	if (!ft_strncmp(key, "a", n))
		return (ft_strdup("hi hi"));
	return (ft_strdup(""));
}

char	*find_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		++i;
	if (i == 0)
		ret = ft_strjoin("$", &str[i]);
	else
		ret = ft_strjoin_free(get_value_n(str, i), &str[i]);
	if(!ret)
		allocat_error();
	free(str);
	return (ret);
}

char	*expand_env_with_quote(char *str)
{
	int 	i;
	char	**temp;
	char 	*ret;

	temp = ft_split(str, "$");
	if (!temp)
		allocat_error();
	i = 0;
	while (temp[++i])
		temp[i] = find_env(temp[i]);
	i = 0;
	while (temp[++i])
		temp[0] = ft_strjoin_free(temp[0], temp[i]);
	ret = ft_strdup(temp[0]);
	split_free(temp);
	return (ret);
}

int main()
{
	char *str = "\"$a wdqwdqwd$a $a$|qwdqwd\"";

	printf("%s\n", expand_env_with_quote(str));
}


if (symbol_lst->type >= T_PIPE && symbol_lst->type != T_LBRACE)
		return(syntax_error_token(get_origin_op(symbol_lst->type)));
	while (symbol_lst->next)
	{
		if (symbol_lst->type == T_LBRACE)
		{
			if (symbol_lst->pre && !(T_PIPE <= symbol_lst->pre->type && symbol_lst->pre->type <= T_LBRACE))
				return (syntax_error_token("("));
			if (symbol_lst->next->type >= T_PIPE && symbol_lst->next->type != T_LBRACE)
				return (syntax_error_token(get_origin_op(symbol_lst->next->type)));
		}
		else if (symbol_lst->type == T_RBRACE)
		{
			if (symbol_lst->next->type < T_PIPE || symbol_lst->next->type == T_LBRACE)
				return (syntax_error_token(symbol_lst->next->str));
		}
		else if (symbol_lst->type >= T_PIPE)
		{
			if (symbol_lst->next->type >= T_PIPE && symbol_lst->next->type != T_LBRACE)
				return (syntax_error_token(get_origin_op(symbol_lst->next->type)));
		}
		symbol_lst = symbol_lst->next;
	}
	if (symbol_lst->pre && symbol_lst->pre->type == T_RBRACE && symbol_lst->type != T_RBRACE)
		return (syntax_error_token(symbol_lst->str));
	if (symbol_lst->type >= T_PIPE && symbol_lst->type != T_RBRACE)
		return (syntax_error_token(get_origin_op(symbol_lst->type)));
	return (0);