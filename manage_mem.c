#include "./include/minishell.h"

void	split_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_symbol(t_symbol *symbols)
{
	int	i;

	i = -1;
	while (symbols[++i].str)
		free(symbols[i].str);
	free(symbols);
}
