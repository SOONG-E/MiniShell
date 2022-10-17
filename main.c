#include "minishell.h"

void	init_shell(char **env)
{
	// set_signal();
	init_info(env);
}

void	execute_cmd(char *str)
{
	t_token	*cmd;

	cmd = parse_line(str);
	execute_tree(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	if (ac != 1 && av)
		return (0);
	init_shell(env);
	while (1)
	{
		str = readline(C_BLUE "minishell$ " C_NRML);
		if (!str)
			exit(0);
		if (!ft_strlen(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		execute_cmd(str);
	}
	return (0);
}
