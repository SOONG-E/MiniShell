#include "./include/minishell.h"

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	**cmd;

    (void)av;
	if (ac != 1)
		return (0);
	//signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	init_info(env);
	//g_envlst = NULL;
	parsing_env(env);
	while (1)
	{
		str = readline(C_BLUE"minishell$ "C_BLCK);
		if (!ft_strlen(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		cmd = parsing_line(str);
		//system("leaks minishell");
	}
	return (0);
}
