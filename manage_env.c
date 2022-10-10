#include "./include/minishell.h"

static int	ft_get_env_len(char *env)
{
	int	len;

	len = 0;
	while (*env && *env != '=')
	{
		env++;
		len++;
	}
	return (len);
}

char	**ft_env_split(char *env)
{
	char	**splited_env;
	int		idx;

	splited_env = (char **)malloc(3 * sizeof(char *));
	if (!splited_env)
		exit(0);
	splited_env[0] = (char *)malloc((ft_get_env_len(env) + 1) * sizeof(char));
	if (!splited_env[0])
		exit(0);
	idx = 0;
	while (*env && *env != '=')
		splited_env[0][idx++] = *env++;
	splited_env[0][idx] = 0;
	env++;
	splited_env[1] = (char *)malloc((ft_get_env_len(env) + 1) * sizeof(char));
	if (!splited_env[1])
		exit(0);
	idx = 0;
	while (*env)
		splited_env[1][idx++] = *env++;
	splited_env[1][idx] = 0;
	splited_env[2] = NULL;
	return (splited_env);
}

char	*get_value_n(char *key, int n)
{
	t_envlst	*temp;

	if (!ft_strcmp(key, "?"))
		return (ft_strdup(g_info->exit_code));

	temp = g_info->envlst;
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
	char	**str;
	int		i;

	i = -1;
	while (env[++i])
	{
		str = ft_env_split(env[i]);
		ft_envlst_add_back(ft_envlst_new(str[0], str[1]));
		free(str);
	}
}


/* ---------seojin -----------*/
char	*ft_get_env(char *key)
{
	t_envlst	*tmp;
	int			len;

	if (*key == '?')
		return (ft_strdup(g_info->exit_code));
	tmp = g_info->envlst;
	len = ft_strlen(key);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
