#include "minishell.h"

static int	check_exit_code(void)
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
//	else
//		excute_pipe_line(tree->symbol);
}