#include "minishell.h"

static int	env_cnt()
{
	int	i;
	t_envlst	*env;

	env = g_info->envlst;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**make_env()
{
	char	**str;
	t_envlst	*env;
	
	str = (char **)ft_calloc(sizeof(char *), env_cnt() + 1);
	if (!str)
		allocat_error();
	env = g_info->envlst;
	while (env)
	{
		
	}
}