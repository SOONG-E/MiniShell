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
		return (0);	// pair error!!!
	}
	//VVV--parsing_cmd.c preprocess_str.c 수정함--VVV
	temp = preprocess_line(str);
	
	symbol_lst = make_symbol_lst(temp);
	
	symbol_lst = expand_env(symbol_lst);//진행중
	printf("%p\n", symbol_lst->pre);
	
	symbolizing(symbol_lst);//수정필요! symbols free 필요! // 심볼리스트로 치환

	/*------------------------------*/
	t_symbol	*test = symbol_lst;
	while (test)
	{
		printf("----------\nstr: %s\ntype: %d\n----------\n", test->str, test->type);
		test = test->next;
	}
	symbol_lst->pre = NULL;
	if (validate(symbol_lst))
	{
		free_symbol(symbol_lst);
		return (0);
	}
	// symbols->type < 0 면 빈 괄호 있는거
	//tree_root = make_parse_tree(symbols);//미구현! //파스트리 생성
	//free_symbol(symbols);
	//return (tree_root);

	//^^^---------------------------------------^^^
	return (NULL);
}
