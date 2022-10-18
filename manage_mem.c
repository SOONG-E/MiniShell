#include "minishell.h"

void	split_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tree(t_token *tree)
{
	t_token	*right_tree;

	if (!tree)
		return ;
	if (tree->left)
		free_tree(tree->left);
	free(tree->symbol);
	right_tree = tree->right;
	free(tree);
	if (right_tree)
		free_tree(right_tree);
}

void	free_symbol(t_symbol *symbol)
{
	if (!symbol)
		return ;
	if (symbol->pre)
		symbol->pre->next = NULL;
	if (symbol->next)
		symbol->next->pre = NULL;
	free(symbol->str);
	free(symbol);
}

void	free_symbols(t_symbol *symbols)
{
	t_symbol	*temp;

	while (symbols)
	{
		temp = symbols;
		free(temp->str);
		symbols = symbols->next;
		free(temp);
	}
}
