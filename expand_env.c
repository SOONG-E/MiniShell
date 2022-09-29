#include "./include/minishell.h"

t_symbol	*sub_env(t_symbol *symbol_lst)
{
	char	*rv;
	char	*tmp;
	int		idx;

	rv = NULL;
	idx = 0;
	while (symbol_lst->str[idx])
	{
		idx += ft_strichr(&symbol_lst->str[idx], '$');
		tmp = rv;
		rv = ft_strndup(symbol_lst->str, idx);
		if (tmp)
			free(tmp);
	}

}

char	*find_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		++i;
	if (i == 0)
		ret = ft_strjoin("$", &str[i]);
	else
		ret = ft_strjoin_free(get_value_n(str, i), &str[i]);
	if(!ret)
		allocat_error();
	free(str);
	return (ret);
}

char	*expand_env_with_quote(char *str)
{
	int 	i;
	char	**temp;
	char 	*ret;

	temp = ft_split(str, "$");
	if (!temp)
		allocat_error();
	i = 0;
	while (temp[++i])
		temp[i] = find_env(temp[i]);
	i = 0;
	while (temp[++i])
		temp[0] = ft_strjoin_free(temp[0], temp[i]);
	ret = ft_strdup(temp[0]);
	split_free(temp);
	return (ret);
}

void	expand_env(t_symbol *symbol_lst)
{
	int	i;
	
	while (symbol_lst)
	{
		symbol_lst->str = expand_env_qoute_case(symbol_lst->str);	
		symbol_lst = symbol_lst->next;
	}
}




















/*
char	*replace_env(char *str)
{
	char	*str_backup;
	char	*ret;
	char	*temp;

	str_backup = str;
	ret = (char *)ft_calloc(sizeof(char), 1);
	if(!ret)
		exit(1);
	while (*str)
	{
		str += cut_temp(&temp, str);
		ret = ft_strjoin_free(ret, temp);
		free(temp);
	}
	free(str_backup);
	return (ret);
}

char	*cut_str1(char *str)
{
	char	*temp;
	char	quote;
	int		i;

	quote = '\0';
	temp = str;
	if (*temp == Q_SINGLE || *temp == Q_DOUBLE)
	{
		quote = *temp;
		temp++;
		if (*temp == quote)
		{
			str = temp + 1;
			return (ft_strdup(""));
		}
	}
	i = 0;
	while (temp[i + 1] != quote)
		i++;
	if (quote == 0)
		str = &temp[i] + 1;
	else
		str = &temp[i] + 2;
	return (ft_substr(temp, 0, i + 1));
}

char	*parse_quote(char *str)
{
	char	**temp;
	char	*str_backup;
	int		i;
	int		num;

	str_backup = str;
	num = count_pair(str);
	temp = (char **)malloc((num + 1) * sizeof(char *));
	if (!temp)
		exit(1);
	i = 0;
	while (i < num)
	{
		if (*str == Q_SINGLE)
			temp[i] = cut_str(&str);
		else
		{
			//temp[i] = replace_env(str);
			//temp[i] = cut_str1(temp[i]);
			temp[i] = cut_str(&str);
			temp[i] = replace_env(temp[i]);
		}
		printf("temp[%d] : %s\n", i, temp[i]);
		i++;
	}
	temp[i] = NULL;
	free(str_backup);
	return (ft_join(temp));
}

void	sub_env(char **temp)
{ 
	int		i;

	i = 0;
	while (temp[i])
	{
		temp[i] = parse_quote(temp[i]);
		i++;
	} 
}
*/