#include "../include/minishell.h"

void	ft_export(char *key, char *value)
{
	t_envlst	*tmp;

	tmp = g_envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	ft_envlst_add_back(ft_envlst_new(key, value));
}

// 정렬, value값에 환경변수 있으면 치환 후 add