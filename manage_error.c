/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:39:24 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 10:01:56 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocat_error(void)
{
	printf("Allocate Error!\n");
	exit(errno);
}

int	error_msg(char *str)
{
	printf("%s: %s\n", SHELL, str);
	set_exit_code(127);
	return (0);
}

void	execute_error(char *cmd_path, char **cmd_arr, char **env)
{
	(void)env;
	(void)cmd_arr;
	(void)cmd_path;
	if (errno == 13)
		printf("%s: %s\n", SHELL, strerror(errno));
	else
	{
		ft_putstr_fd("minihell: command not found: ", STDERR);
		ft_putstr_fd(cmd_arr[0], STDERR);
		ft_putstr_fd("\n", STDERR);
	}
	if (cmd_path)
		free(cmd_path);
	if (cmd_arr && *cmd_arr)
		split_free(cmd_arr);
	if (env)
		split_free(env);
	exit(127);
}

int	open_file_error(char *file)
{
	ft_putstr_fd("minihell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(strerror(errno), STDERR);
	ft_putstr_fd("\n", STDERR);
	return (-1);
}
