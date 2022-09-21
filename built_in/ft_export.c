#include "../include/minishell.h"

void	sort_env(void)
{

}

void	ft_export(char *key, char *value)
{
	ft_lst_add_back(ft_lst_new(key, value));
}