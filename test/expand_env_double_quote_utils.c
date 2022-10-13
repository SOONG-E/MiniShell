#include "minishell.h"

static int	ft_count(char *str, char chr)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == chr)
			++count;
	}
	return (count);
}

static char	*ft_strcpy(char *str, int s, int e)
{
	char	*save;
	int		i;

	save = (char *)malloc((e - s + 1) * sizeof(char));
	i = 0;
	while (s < e)
	{
		save[i] = str[s];
		i++;
		s++;
	}
	save[i] = 0;
	return (save);
}

static char	**ft_putstr2(char **save, char *str, char chr, int count)
{
	int	i;
	int	start;
	int	end;	

	i = 0;
	start = 0;
	while (i <= count)
	{
		end = start;
		while (str[end] && str[end] != chr)
			++end;
		save[i] = ft_strcpy(str, start, end);
		start = end + 1;
		++i;
	}
	return (save);
}

char	**double_quote_split(char *str, char chr)
{
	int		count;
	char	**save;

	count = ft_count(str, chr);
	save = (char **)malloc(sizeof(char *) * (count + 2));
	if (save == NULL)
		allocat_error();
	save[count + 1] = NULL;
	save = ft_putstr2(save, str, chr, count);
	return (save);
}
