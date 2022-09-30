#include "./include/minishell.h"

static int	check_pair(char *str)
{	
	while (*str)
	{
		if (*str == Q_SINGLE)
		{
			str++;
			str = ft_strchr(str, Q_SINGLE);
		}
		else if (*str == Q_DOUBLE)
		{
			str++;
			str = ft_strchr(str, Q_DOUBLE);
		}
		else if (*str == ')')
			return (0);
		else if (*str == '(')
		{
			str++;
			str = ft_strchr(str, ')');
		}
		if (!str)
			return (0);
		str++;
	}
	return (1);
}

char	**parsing_line(char *str)
{
	char		**temp;
	t_symbol	*symbol_lst;
	//t_token	*tree_root;

	if (!check_pair(str))
		exit(1);	// pair error!!!
	//VVV--parsing_cmd.c preprocess_str.c 수정함--VVV
	temp = preprocess_line(str);
	printf("preprocess_line 성공!\n");
	symbol_lst = make_symbol_lst(temp);
	printf("make_symbol_lst 성공!\n");
	symbol_lst = expand_env(symbol_lst);//진행중
	printf("expand_env 성공!\n");
	while (symbol_lst)
	{
		printf("%s\n", symbol_lst->str);
		symbol_lst = symbol_lst->next;
	}
	free_symbol(symbol_lst);
	
	//symbols = symbolizing(symbol_lst);//수정필요! symbols free 필요! // 심볼리스트로 치환
	// symbols->type < 0 면 빈 괄호 있는거
	//tree_root = make_parse_tree(symbols);//미구현! //파스트리 생성
	//free_symbol(symbols);
	//return (tree_root);

	//^^^---------------------------------------^^^
	return (NULL);
}
