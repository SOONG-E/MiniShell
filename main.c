#include "minishell.h"

void	init_shell(char **env)
{
	// rl_catch_signals = 0;
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, sigint_handler);
	init_info(env);
}

void	search_tree(t_token	*tree);

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*cmd;

    (void)env;
	(void)av;
	if (ac != 1)
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
		cmd = parse_line(str);
	//	search_tree(cmd);
	}
	return (0);
}
