/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:47 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:34:02 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*brace_group(t_symbol *symbol)
{
	t_symbol	*temp;

	symbol = symbol->next;
	if (symbol->pre)
		symbol->pre->next = NULL;
	free_symbol(symbol->pre);
	symbol->pre = NULL;
	temp = get_last_symbol(symbol);
	temp = temp->pre;
	if (temp->next)
		temp->next->pre = NULL;
	free_symbol(temp->next);
	temp->next = NULL;
	return (and_or(symbol));
}
