#include "./include/minishell.h"

char	*get_value_n(char *key, int n)
{
	t_envlst	*temp;
	
	temp = g_envlst;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, n))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

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
