#include "./include/minishell.h"



void	replace_backup(char	**temp)
{
	int	i;
	int	j;
	
	i = 0;
	while (temp[i])
	{
		j = 0;
		while(temp[i][j])
		{
			if (temp[i][j] < 0)
				temp[i][j] *= -1;
			j++;
		}
		i++;
	}
}

void	tokenizing(char	*str)
{
	char	**temp;
	
	replace_white_space(str);
	temp = ft_split(str, "\n\t\v\f\r ");
	replace_backup(temp);
	sub_env(temp);
}

int	check_quote(char *str)
{	
	while (*str)
	{
		if (*str == Q_SINGLE)
		{
			str++;
			str = ft_strchr(str, Q_SINGLE);
			if (!str)
				return (0);
		}
		else if (*str == Q_DOUBLE)
		{
			str++;
			str = ft_strchr(str, Q_DOUBLE);
			if (!str)
				return (0);
		}
		str++;
	}
	return (1);
}

char	**parsing_cmd(char *str)
{
	if (!check_quote(str))
	{
		printf("잘못됨\n");//////////quote에러!!!!
		return (NULL);
	}
	tokenizing(str);
	return (NULL);
}