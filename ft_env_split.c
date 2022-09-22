#include "./include/minishell.h"

static int	ft_get_env_len(char *env);

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
