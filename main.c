#include "./include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	**cmd;

    (void)av;
	if (ac != 1)
		return (0);
	init_info(env);
	//g_envlst = NULL;
	parsing_env(env);
	while (1)
	{
		str = readline("minishell$ ");
		if (!ft_strlen(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		cmd = parsing_line(str);
		if (!cmd)
			set_exit_code(127); // d임시
		system("leaks minishell");
	}
	return (0);
}
