#include "./include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	**cmd;

    (void)av;
	if (ac != 1)
		return (0);
	g_envlst = NULL;
	parsing_env(env);
	while (1)
	{
		str = readline("minishell$ ");
		if (!ft_strlen(str))
			continue ;
		add_history(str);
		cmd = parsing_line(str);
		system("leaks minishell");
		//free(str);
	}
	return (0);
}
