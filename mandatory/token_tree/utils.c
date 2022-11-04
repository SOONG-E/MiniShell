/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:52 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 11:00:35 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
