/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:25 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 11:01:48 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_bonus.h"

void	execute(char *str)
{
	t_token	*cmd;

	cmd = parse_line(str);
	execute_tree(cmd);
	free_tree(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	if (ac != 1 && av)
		return (0);
	init_info(env);
	while (1)
	{
		set_signal();
		str = readline(C_BLUE "minihell$ " C_NRML);
		if (!str)
			exit(0);
		if (!ft_strlen(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		execute(str);
	}
	return (0);
}
