#include "minishell.h"

static void	backup_white_space(char	**temp);

char	**preprocess_line(char *str)
{
	char	**temp;

	str = replace_op(str);
	replace_white_space(str);
	temp = ft_split(str, "\n\t\v\f\r ");
	if (!temp)
		allocat_error();
	backup_white_space(temp);
	free(str);
	return (temp);
}

static void	backup_white_space(char	**temp)
{
	int	i;
	int	j;

	i = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j] < 0 && temp[i][j] > -40)
				temp[i][j] *= -1;
			j++;
		}
		i++;
	}
}
