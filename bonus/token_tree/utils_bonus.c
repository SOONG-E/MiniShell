/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:52 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:52:47 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_symbol	*skip_brace(t_symbol *symbol)
{
	int	cnt;

	cnt = 1;
	while (symbol)
	{
		if (symbol->type == T_LBRACE)
			cnt--;
		else if (symbol->type == T_RBRACE)
			cnt++;
		if (cnt == 0)
			break ;
		symbol = symbol->pre;
	}
	return (symbol);
}
