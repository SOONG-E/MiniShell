#include "./include/minishell.h"

// char	*ft_join(char **str)
// {
// 	char	*ret;
// 	int		idx;

// 	idx = 0;
// 	while (str[++idx])
// 		str[0] = ft_strjoin_free(str[0], str[idx]);
// 	ret = ft_strdup(str[0]);
// 	split_free(str);
// 	printf("after ft_join = %s\n", ret);
// 	return (ret);
// }

// int	count_pair(char *str)
// {
// 	int	count;

// 	count = 0;
// 	while (*str)
// 	{	
// 		++count;
// 		if (*str == Q_SINGLE)
// 		{
// 			++str;
// 			str = ft_strchr(str, Q_SINGLE);
// 		}
// 		else if (*str == Q_DOUBLE)
// 		{
// 			++str;
// 			str = ft_strchr(str, Q_DOUBLE);
// 		}
// 		else
// 		{
// 			while (*str && *str != Q_DOUBLE && *str != Q_SINGLE)
// 				++str;
// 			continue ;
// 		}
// 		++str;
// 	}
// 	return (count);
// }

// char	*cut_str(char **str)
// {
// 	char	*temp;
// 	char	quote;
// 	int		i;

// 	quote = '\0';
// 	temp = *str;
// 	if (*temp == Q_SINGLE || *temp == Q_DOUBLE)
// 	{
// 		quote = *temp;
// 		temp++;
// 		if (*temp == quote)
// 		{
// 			*(str) = temp + 1;
// 			return (ft_strdup(""));
// 		}
// 	}
// 	i = 0;
// 	while (temp[i + 1] != quote)
// 		i++;
// 	if (quote == 0)
// 		*(str) = &temp[i] + 1;
// 	else
// 		*(str) = &temp[i] + 2;
// 	return (ft_substr(temp, 0, i + 1));
// }

// int	cut_temp(char **temp, char *str)
// {
// 	int		i;

// 	i = 0;
// 	if (str[0] == '$')
// 	{
// 		str++;
// 		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 			i++;
// 		*(temp) = get_value_n(str, i);
// 		return (i + 1);
// 	}
// 	while (str[i] && str[i] != '$')
// 		i++;
// 	*(temp) = ft_substr(str, 0, i);
// 	return (i);
// }


/*--------------------------------------------*/
char	*ft_get_value(char *str, int *idx)
{
	int		len;
	char	*key;
	char	*value;

	len = 0;
	if (str[len] == '?')
	{
		*idx += 1;
		return (ft_get_env("?"));
	}
	while (ft_is_alnum(str[len]) || str[len] == '_')
	{
		len++;
		*idx += 1;
	}
	if (len == 0)
		return (NULL);
	key = ft_substr(str, 0, len);
	value = ft_get_env(key);
	free(key);
	return (value);
}

void	ft_skip_quote(char *str, int *idx, int flag)
{
	str++;
	if (flag == Q_SINGLE)
	{
		while (*str != Q_SINGLE)
		{
			str++;
			*idx += 1;
		}
		*idx += 2;
	}
	else
	{
		while (*str != Q_DOUBLE)
		{
			str++;
			*idx += 1;
		}
		*idx += 2;
	}
}

char	*ft_new_str(char *str, char *key, int *idx)
{
	int		len;
	char	*value;
	char	*s1;
	char	*s2;
	char	*s3;

	len = 0;
	value = ft_get_value(key, &len);
	if (!value)
	{
		*idx += 1;
		return (str);
	}
	s1 = ft_substr(str, 0, key - str - 1);
	s2 = ft_strjoin(s1, value);
	free(s1);
	s1 = ft_strdup(key + len);
	s3 = ft_strjoin(s2, s1);
	*idx += ft_strlen(value);
	free(s1);
	free(s2);
	free(str);
	free(value);
	return (s3);
}

void	ft_backup_space_symbol(t_symbol *symbol)
{
	char	*str;
	int		idx;

	while (symbol)
	{
		str = symbol->str;
		idx = 0;
		while (str[idx])
		{
			if (str[idx] < 0 && str[idx] > -40)
				str[idx] *= -1;
			idx++;
		}
		symbol = symbol->next;
	}
}

t_symbol	*ft_update_symbol(t_symbol *symbol, t_symbol *new)
{
	t_symbol	*tmp;

	if (new)
	{
		symbol->pre->next = new;
		new->pre = symbol->pre;
		if (symbol->next)
		{
			symbol->next->pre = ft_get_last_symbol(new);
			ft_get_last_symbol(new)->next = symbol->next;
		}
	}
	else
	{
		symbol->pre->next = symbol->next;
		if (symbol->next)
			symbol->next->pre = symbol->pre;
	}
	tmp = symbol->next;
	free(symbol->str);
	free(symbol);
	symbol = tmp;
	return (symbol);
}
