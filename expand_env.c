#include "./include/minishell.h"

//update function name plz...
int	is_alnum_under(char c)
{	// ft_isalnum  안쓰는 이유가 뭐죠?
	if ('0' <= c && c <= '9')
		return (1);
	else if ('A' <= c && c <= 'Z')
		return (1);
	else if ('a' <= c && c <= 'z')
		return (1);
	else if ('a' == '_')
		return (1);
	else
		return (0);
}

t_symbol	*make_sub_lst(char *value)
{
	t_symbol	*new_node;
	char		**tmp;
	int			i;

	new_node = NULL;
	tmp = ft_split(value, " ");
	i = 0;
	while (tmp[i])
	{
		lst_symbol_add_back(&new_node, ft_symbol_new(tmp[i]));
		i++;
	}
	split_free(tmp);
	return (new_node);
}

t_symbol	*expand_basic_env(char *str, int *idx)
{
	t_symbol	*new_symbol;
	char		*key;
	char		*value;
	int			i;

	i = 0;
	while (str[i + 1] && is_alnum_under(str[i + 1]))
	{
		(*idx)++;
		i++;
	}
	(*idx)++;
	key = ft_substr(str, 1, i);
	value = get_value_n(key, i);
	if (ft_strichr(value, ' ') == -1)
		return (ft_symbol_new(value));
	new_symbol = make_sub_lst(value);
	//free(key);
	//free(value);
	return (new_symbol);
}

t_symbol	*combine_lst(t_symbol *first_lst, t_symbol *second_lst)
{
	t_symbol	*temp_lst;

	temp_lst = first_lst;
	while (first_lst->next)
	{
		first_lst = first_lst->next;
	}
	first_lst->str = ft_strjoin_free(first_lst->str, second_lst->str);
	first_lst->next = second_lst->next;
	//free(second_lst->str);
	//free(second_lst);
	return (temp_lst);
}

t_symbol	*get_temp_lst(char *str)
{
	t_symbol	*temp_lst;
	int			e;
	int			s;

	e = 0;
	temp_lst = ft_symbol_new(ft_strdup(""));
	while (e >= 0 && str[e])
	{
		s = e;
		if (str[s] == '$')
			temp_lst = combine_lst(temp_lst, expand_basic_env(&str[e], &e));
		else
		{
			e = ft_strichr(str, '$');
			if (e > 0)
				temp_lst = combine_lst(temp_lst, ft_symbol_new(ft_substr(str, s, e - s)));
			else
				temp_lst = combine_lst(temp_lst, ft_symbol_new(ft_strdup(&str[s])));
		}
	}
	return (temp_lst);
}

void	expand_env(t_symbol *symbol_lst)
{
	t_symbol	*temp_lst;
	
	while (symbol_lst)
	{
		symbol_lst->str = expand_env_quote_case(symbol_lst->str);
		if (ft_strichr(symbol_lst->str, '$') < 0)
		{
			symbol_lst = symbol_lst->next;
			continue ;
		}
		temp_lst = get_temp_lst(symbol_lst->str);
		symbol_lst->pre->next = temp_lst;
		lst_symbol_add_back(&temp_lst, symbol_lst->next);
		//free(symbol_lst->str);
		//free(symbol_lst);
		symbol_lst = temp_lst->next;
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