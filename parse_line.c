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

void search_tree(t_token *tree);

char	**parse_line(char *str)
{
	char		**temp;
	t_symbol	*symbol_lst;
	t_token		*tree_root;

	if (!check_pair(str))
	{
		free(str);
		error_msg("incomplete command");
		return (0);
	}
	temp = preprocess_line(str);
	symbol_lst = make_symbol_lst(temp);
	symbol_lst = expand_env(symbol_lst);
	if (!symbol_lst)
		return (0);
	symbolizing(symbol_lst);
	if (validate(symbol_lst))
	{
		free_symbols(symbol_lst);
		return (0);
	}
	expand_filename(symbol_lst);
	/*--------------test--------------*/
	//t_symbol *tmp = symbol_lst;
	// while (tmp)
	// {
	// 	printf("--------------\nstr: %s\ntype: %d\n-----------------\n", tmp->str, tmp->type);
	// 	tmp = tmp->next;
	// }
	//tmp = sort_redirection(symbol_lst);
	// printf("\n\n---------after sort--------\n");
	// while (tmp)
	// {
	// 	printf("--------------\nstr: %s\ntype: %d\n-----------------\n", tmp->str, tmp->type);
	// 	tmp = tmp->next;
	// }
	/*--------------^^^^---------------*/
	tree_root = make_parse_tree(symbol_lst);
	printf("-------tree test------------\n");
	search_tree(tree_root);
	//free_symbols(symbol_lst);
	//return (tree_root);
	return (0);
}
