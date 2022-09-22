#include "./include/minishell.h"

int	count_amount(char **temp)
{
	int	count;

	count = 0;
	while (temp[count])
		++count;
	return (count);
}

t_symbol	*symbolizing(char **temp)
{
	t_symbol	*symbols;

	symbols = (t_symbol *)ft_calloc((count_amount(temp) + 1), sizeof(t_symbol));
	if (!symbols)
		allocat_error();
	//put_str(temp, &symbols);

	int i = -1;
	while (++i < size)
		printf("%d ", symbols[i].type);
}