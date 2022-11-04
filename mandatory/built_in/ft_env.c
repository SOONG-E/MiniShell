/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:16 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 11:00:24 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(char **arg, int pipe_cnt)
{
	t_envlst	*tmp;

	tmp = g_info->envlst;
	if (arg[1])
	{
		printf("env: %s: No such file or directory\n", arg[1]);
		if (pipe_cnt)
			exit(127);
		set_exit_code(127);
		return ;
	}
	while (tmp)
	{
		if (tmp->value)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	if (pipe_cnt)
		exit(0);
	set_exit_code(0);
}
