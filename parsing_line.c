#include "./include/minishell.h"

static int	check_pair(char *str)
{
	int	cnt_brace;

	cnt_brace = 0;
	while (*str)
	{
		if (*str == Q_SINGLE)
			str = ft_strchr(++str, Q_SINGLE);
		else if (*str == Q_DOUBLE)
			str = ft_strchr(++str, Q_DOUBLE);
		else if (*str == '(')
			cnt_brace++;
		else if (*str == ')')
			cnt_brace--;
		if (!str || cnt_brace < 0)
			return (0);
		str++;
	}
	if (cnt_brace)
		return (0);
	return (1);
}

char	**parsing_line(char *str)
{
	char		**temp;
	t_symbol	*symbol_lst;
	//t_token	*tree_root;

	if (!check_pair(str))
	{
		free(str);
		error_msg("incomplete command");
		return (0);
	}
	temp = preprocess_line(str);
	symbol_lst = make_symbol_lst(temp);
	symbol_lst = expand_env(symbol_lst);//진행중
	symbolizing(symbol_lst);
	if (validate(symbol_lst))
	{
		free_symbol(symbol_lst);
		return (0);
	}
	t_symbol *tmp = symbol_lst;
	while (tmp)
	{
		printf("--------------\nstr: %s\ntype: %d\n-----------------\n", tmp->str, tmp->type);
		tmp = tmp->next;
	} 
	//tree_root = make_parse_tree(symbols);//미구현! //파스트리 생성
	free_symbol(symbol_lst);
	//return (tree_root);

	//^^^---------------------------------------^^^
	return (0);
}
