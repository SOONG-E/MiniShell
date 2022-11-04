/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:24 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 11:00:35 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*pipe_get_name(char *arg);
static void	pipe_print_export(void);

void	ft_pipe_export(char **arg)
{
	char	*name;
	int		idx;

	if (!arg[1])
		return (pipe_print_export());
	idx = 1;
	while (arg[idx])
	{
		name = pipe_get_name(arg[idx]);
		if (!name)
		{
			printf("%s: export: `%s': not a valid identifier\n", \
			SHELL, arg[idx]);
			exit(127);
		}
		free(name);
		++idx;
	}
	exit(0);
}

static char	*pipe_get_name(char *arg)
{
	int	idx;

	idx = 1;
	if (!ft_isalpha(arg[0]) || arg[0] != '_')
		return (NULL);
	while (arg[idx] && arg[idx] != '=')
	{
		if (!ft_isalnum(arg[idx]) && arg[idx] != '_')
			return (NULL);
		idx++;
	}
	return (ft_substr(arg, 0, idx));
}

static void	pipe_print_export(void)
{
	t_envlst	*temp;

	temp = g_info->envlst;
	while (temp)
	{
		write(1, "declare -x ", 11);
		write(1, temp->key, ft_strlen(temp->key));
		if (temp->value)
		{
			write(1, "=\"", 1);
			write(1, temp->value, ft_strlen(temp->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		temp = temp->next;
	}
	exit(0);
}
