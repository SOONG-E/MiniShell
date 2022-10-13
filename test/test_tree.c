
#include "../include/minishell.h"

void	test_execute(t_symbol *symbol)
{
	t_symbol	*temp;
	temp = symbol;
	while (temp)
	{
		printf("%s  ", temp->str);
		temp = temp->next;
	}
	if (!ft_strcmp(symbol->str, "1"))
	{
		printf("OK!\n");
		set_exit_code(0);
	}
	else
	{
		printf("KO!\n");
		set_exit_code(127);
	}
}

int	check_exit_code(void)
{
	if (ft_strlen(g_info->exit_code) == 1 && g_info->exit_code[0] == '0')
		return (0);
	else
		return (1);
}

void	search_tree(t_token	*tree)
{
	if (!tree)
		return ;
	if (tree->left)
		search_tree(tree->left);
	if	(tree->symbol->type == T_AND_IF || tree->symbol->type == T_OR_IF)
	{
		if ((tree->symbol->type == T_AND_IF && !check_exit_code())
			|| (tree->symbol->type == T_OR_IF && check_exit_code()))
			search_tree(tree->right);
	}
	else
		test_execute(tree->symbol);
}