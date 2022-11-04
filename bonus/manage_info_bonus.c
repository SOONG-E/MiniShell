/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_info_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:29 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 11:01:48 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_bonus.h"

void	init_info(char **env)
{
	g_info = (t_info *)malloc(sizeof(t_info));
	g_info->envlst = NULL;
	parse_env(env);
	g_info->exit_code = ft_itoa(0);
	g_info->oldpwd_flag = 0;
	g_info->home = get_env("HOME");
}

void	set_exit_code(int code)
{
	free(g_info->exit_code);
	g_info->exit_code = ft_itoa(code);
}
