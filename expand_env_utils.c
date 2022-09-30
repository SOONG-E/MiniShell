#include "./include/minishell.h"

char	*ft_join(char **str)
{
	char	*ret;
	int		idx;

	idx = 0;
	while (str[++idx])
		str[0] = ft_strjoin_free(str[0], str[idx]);
	ret = ft_strdup(str[0]);
	split_free(str);
	printf("after ft_join = %s\n", ret);
	return (ret);
}

int	count_pair(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{	
		++count;
		if (*str == Q_SINGLE)
		{
			++str;
			str = ft_strchr(str, Q_SINGLE);
		}
		else if (*str == Q_DOUBLE)
		{
			++str;
			str = ft_strchr(str, Q_DOUBLE);
		}
		else
		{
			while (*str && *str != Q_DOUBLE && *str != Q_SINGLE)
				++str;
			continue ;
		}
		++str;
	}
	return (count);
}

char	*cut_str(char **str)
{
	char	*temp;
	char	quote;
	int		i;

	quote = '\0';
	temp = *str;
	if (*temp == Q_SINGLE || *temp == Q_DOUBLE)
	{
		quote = *temp;
		temp++;
		if (*temp == quote)
		{
			*(str) = temp + 1;
			return (ft_strdup(""));
		}
	}
	i = 0;
	while (temp[i + 1] != quote)
		i++;
	if (quote == 0)
		*(str) = &temp[i] + 1;
	else
		*(str) = &temp[i] + 2;
	return (ft_substr(temp, 0, i + 1));
}

int	cut_temp(char **temp, char *str)
{
	int		i;

	i = 0;
	if (str[0] == '$')
	{
		str++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		*(temp) = get_value_n(str, i);
		return (i + 1);
	}
	while (str[i] && str[i] != '$')
		i++;
	*(temp) = ft_substr(str, 0, i);
	return (i);
}
