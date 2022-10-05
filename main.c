#include "./include/minishell.h"

int	is_end_op(char *str)
{
	int	idx;

	idx = ft_strlen(str);
	if (idx > 1)
		if (!ft_strcmp(str[idx - 2], "&&"))
			return (1);
	else if (!ft_strcmp(str[idx - 2], "||"))
		return (1);
	if (!ft_strcmp(str[idx - 1], "|")),
}

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
		while ()
		{
			readline("> ");
		}
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
