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
	printf("\n");
	temp = tree->symbol;	
	while (temp)
	{
		if (temp->str)
			printf(" %d %s |", temp->type, temp->str);
		temp = temp->next;
	}
	printf("\n");	
	if (tree->right)
	{
		search_tree(tree->right);
	//	free(tree->right);
	}
}
