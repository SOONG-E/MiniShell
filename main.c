
#include "./include/minishell.h"

int main(int ac, char **av, char **env)
{
	char  	*str;
	char	**cmd;

    (void)av;
	if (ac != 1)
		return (0);
	g_envlst = NULL;
	parsing_env(env);
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		cmd = parsing_cmd(str);
		//free(str);
		system("leaks minishell");
	}
	return (0);
}
