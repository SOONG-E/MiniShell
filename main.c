
#include "./include/minishell.h"

void	parsing_env(char **env)
{
    char    	**str;
	int			i;

	i = -1;
	while (env[++i])
	{
		str = ft_env_split(env[i]);
		ft_lst_add_back(ft_lst_new(str[0], str[1]));
		free(str);
	}
}

int main(int ac, char **av, char **env)
{
	char    *str;
	char	**cmd;

    (void)av;
	if (ac != 1)
		return (0);
	g_envlst = NULL;
	parsing_env(env);
	while (1)
	{
		str = readline("minishell$ ");
		str = preprocess_str(str);
		add_history(str);
		cmd = parsing_cmd(str);
		free(str);
	}
	return (0);
}
