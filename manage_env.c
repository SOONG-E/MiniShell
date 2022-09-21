#include "./include/minishell.h"

char	*get_value_n(char *key, int n)
{
	t_envlst	*temp;
	
	temp = g_envlst;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, n))
			return (temp->value);
		temp = temp->next;
	}
	return (ft_strdup(""));
}