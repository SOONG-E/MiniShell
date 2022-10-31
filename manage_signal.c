/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:33 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:47 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	set_exit_code(1);
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_info->flag = 1;
}

void	set_child_signal(void)
{
	rl_catch_signals = 1;
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(errno);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(errno);
}

void	block_signal(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(errno);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(errno);
}

void	set_signal(void)
{
	rl_catch_signals = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(errno);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit(errno);
}
