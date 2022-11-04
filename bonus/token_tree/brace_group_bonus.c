/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_group_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:47 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:52:47 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
