#include "./include/minishell.h"

t_token	*make_token_recursive(t_symbol *symbols, int type_curr_token, t_child_info *(**get_child_info)(t_symbol *))
{
	t_child_info	*child_info;
	t_token			*token_node;

	token_node = (t_token *)malloc(sizeof(t_token));
	if (symbols->next == NULL && symbols->pre == NULL)//노드 하나인 경우
	{
		token_node->left = NULL;
		token_node->right = NULL;
		return (token_node);
	}
	else
	{
		child_info = get_child_info[type_curr_token](symbols);
		token_node->left = make_token_recursive(child_info->left_symbol, child_info->left_token, get_child_info);
		token_node->right = make_token_recursive(child_info->right_symbol, child_info->right_token, get_child_info);
		free(child_info);
	}
	return (token_node);
}

t_token	*make_parse_tree(t_symbol *symbols)
{
	t_token			*tree_root;
	t_child_info	(*get_child_info[11])(t_symbol *);

	tree_root = NULL;//??
	set_tree_function(get_child_info);
	tree_root = make_token_recursive(symbols, TK_AND_OR, get_child_info);
	return (tree_root);
}

// get and_or info



/*VVVVVVVVVVVVVVVVVVVVVVV공용 함수*VVVVVVVVVVVVVVVVVVVVVVV*/

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/




t_token	*make_token_tree(t_symbol *symbol, int token)
{
			
}