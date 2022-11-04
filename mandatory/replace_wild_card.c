/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wild_card.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:46 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 11:02:06 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	replace_back_wild_card(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] < 0)
				str[i][j] *= -1;
			j++;
		}
		i++;
	}
}

void	replace_wild_card(char *str)
{
	while (*str)
	{
		if (*str == Q_DOUBLE)
		{
			str++;
			while (*str != Q_DOUBLE)
			{
				if (*str == '*')
					*str *= -1;
				str++;
			}
		}
		if (*str == Q_SINGLE)
		{
			str++;
			while (*str != Q_SINGLE)
			{
				if (*str == '*')
					*str *= -1;
				str++;
			}
		}
		str++;
	}
}
