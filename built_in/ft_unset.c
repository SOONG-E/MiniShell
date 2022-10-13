#include "minishell.h"

static int	arg_vaild_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] != '_')
			return (0);
		i++;
	}
	return (1);
	
}

static void	delete_env_lst(char *str)
{
	t_envlst	*tmp;
	t_envlst	*free_tmp;

	tmp = g_info->envlst;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->next->key, str) == 0)
		{
			free_tmp = tmp->next;
			tmp->next = tmp->next->next;
			free(free_tmp->key);
			free(free_tmp->value);
			free(free_tmp);
		}
		tmp = tmp->next;
	}
}

void	ft_unset(char **arg, int pipe_cnt)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg_vaild_check(arg[i]))
		{
			printf("%s: unset: '%s': not a valid identiier\n", SHELL, arg[i]);
			set_exit_code(1);
			return ;
		}
		else if(pipe_cnt)
		{
			delete_env_lst(arg[i]);
		}
		i++;
	}
	set_exit_code(0);
}
