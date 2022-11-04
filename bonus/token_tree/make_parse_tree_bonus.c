/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_parse_tree_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:50 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 11:02:26 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

t_token	*make_token(t_symbol *symbol)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(-1);
	token->symbol = symbol;
	token->left = NULL;
	token->right = NULL;
	return (token);
}

t_token	*make_parse_tree(t_symbol *symbol)
{
	t_token			*tree_root;

	tree_root = and_or(symbol);
	return (tree_root);
}
