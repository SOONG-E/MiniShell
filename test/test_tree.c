#include "../include/minishell.h"

void search_tree(t_token *tree)
{
	t_symbol *temp;

	if (!tree)
		return ;
	if (tree->left)
	{
		search_tree(tree->left);
		//free(tree->left);
	}
	while (tree->symbol)
	{
		temp = tree->symbol;
		printf("%s  ", tree->symbol->str);
		tree->symbol = tree->symbol->next;
	//	free(temp);
	}
	printf("\n");	
	if (tree->right)
	{
		search_tree(tree->right);
	//	free(tree->right);
	}
}
