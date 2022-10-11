#include "./include/minishell.h"

static char		*expand_env_in_double_quote(char *str);
static t_symbol	*expand_env_out_quote(char *str);


t_symbol	*expand_env(t_symbol *symbol)
{
	t_symbol	*head;
	t_symbol	*new;

	head = new_symbol("");
	head->next = symbol;
	symbol->pre = head;
	while (symbol)
	{
		if (ft_strchr(symbol->str, '$'))
		{
			symbol->str = expand_env_in_double_quote(symbol->str);
			replace_white_space(symbol->str);
			new = expand_env_out_quote(symbol->str);
			backup_space_symbol(new);
			symbol = update_symbol(symbol, new);
		}
		else
			symbol = symbol->next;
	}
	symbol = head->next;
	if (symbol)
		symbol->pre = NULL;
	free(head->str);
	free(head);
	return (symbol);
}

static char	*expand_env_in_double_quote(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == Q_SINGLE)
			skip_quote(&str[idx], &idx, Q_SINGLE);
		else if (str[idx] == Q_DOUBLE)
		{
			idx++;
			while (str[idx] != Q_DOUBLE)
			{
				if (str[idx] == '$')
					str = new_str(str, &str[idx + 1], &idx);
				else
					idx++;
			}
			idx++;
		}
		else
			idx++;
	}
	return (str);
}

static t_symbol	*expand_env_out_quote(char *str)
{
	int			idx;
	char		**str_2d;
	t_symbol	*head;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == Q_SINGLE || str[idx] == Q_DOUBLE)
			skip_quote(&str[idx], &idx, str[idx]);
		else if (str[idx] == '$')
			str = new_str(str, &str[idx + 1], &idx);
		else
			idx++;
	}
	head = NULL;
	str_2d = ft_split(str, "\n\t\v\f\r ");
	idx = 0;
	while (str_2d[idx])
	{
		add_back_symbol(&head, new_symbol(str_2d[idx]));
		free(str_2d[idx++]);
	}
	free(str_2d);
	free(str);
	return (head);
}
// int	is_alnum_under(char c)
// {
// 	if (ft_isalnum(c))
// 		return (1);
// 	else if (c == '_')
// 		return (1);
// 	else
// 		return (0);
// }

// t_symbol	*make_sub_lst(char *value)
// {
// 	t_symbol	*new_node;
// 	char		**temp;
// 	int			i;

// 	new_node = NULL;
// 	temp = ft_split(value, " ");
// 	i = 0;
// 	while (temp[i])
// 	{
// 		lst_symbol_add_back(&new_node, ft_symbol_new(temp[i]));
// 		i++;
// 	}
// 	free(temp);
// 	return (new_node);
// }

// t_symbol	*expand_basic_env(char *str, int *idx)
// {
// 	t_symbol	*new_symbol;
// 	char		*key;
// 	char		*value;
// 	int			i;

// 	i = 0;
// 	while (str[i + 1] && is_alnum_under(str[i + 1]))
// 	{
// 		(*idx)++;
// 		i++;
// 	}
// 	(*idx)++;
// 	key = ft_substr(str, 1, i);
// 	value = get_value_n(key, i);
// 	if (ft_strichr(value, ' ') == -1)
// 	{
// 		free(key);
// 		return (ft_symbol_new(value));
// 	}
// 	new_symbol = make_sub_lst(value);
// 	free(key);
// 	free(value);
// 	return (new_symbol);
// }

// char	*make_single_str(char *str, int *idx)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	while (str[i] != '$' && str[i])
// 	{
// 		if (str[i] == Q_SINGLE)
// 			i += ft_skip_single_qoute(&str[i]);
// 		else
// 			i++;
// 	}
// 	ret = ft_substr(str, 0, i);
// 	*idx += i;
// 	return (ret);
// }

// t_symbol	*combine_lst(t_symbol *first_lst, t_symbol *second_lst)
// {
// 	t_symbol	*temp_lst;

// 	temp_lst = first_lst;
// 	while (first_lst->next)
// 		first_lst = first_lst->next;
// 	first_lst->str = ft_strjoin_free(first_lst->str, second_lst->str);
// 	first_lst->next = second_lst->next;
// 	free(second_lst->str);
// 	free(second_lst);
// 	return (temp_lst);
// }

// void	ft_skip_quote(char *str, int *idx, int flag)
// {
// 	str++;
// 	if (flag == Q_SINGLE)
// 	{
// 		while (*str != Q_SINGLE)
// 		{
// 			str++;
// 			*idx += 1;
// 		}
// 		*idx += 2;
// 	}
// 	else
// 	{
// 		while (*str != Q_DOUBLE)
// 		{
// 			str++;
// 			*idx += 1;
// 		}
// 		*idx += 2;
// 	}
// }

// t_symbol	*get_temp_lst(char *str)
// {
// 	t_symbol	*temp_lst;
// 	int			i;

// 	temp_lst = ft_symbol_new(ft_strdup(""));
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == Q_SINGLE || str[i] == Q_DOUBLE)
// 			ft_skip_quote(&str[i], &i, str[i]);
// 		else if (str[i] == '$')
// 			temp_lst = combine_lst(temp_lst, expand_basic_env(&str[i], &i));
// 		else
// 			temp_lst = combine_lst(temp_lst, ft_symbol_new(make_single_str(&str[i], &i)));
// 	}
// 	return (temp_lst);
// }


// t_symbol	*expand_env(t_symbol *symbol_lst)
// {
// 	t_symbol	*head;
// 	t_symbol	*temp_lst;

// 	head = ft_symbol_new(ft_strdup("head"));
// 	head->next = symbol_lst;
// 	symbol_lst->pre = head;
	
// 	while (symbol_lst)
// 	{
// 		if (ft_strichr(symbol_lst->str, '$') >= 0)
// 		{
// 			symbol_lst->str = expand_env_quote_case(symbol_lst->str);

// 			printf("1. %s\n", symbol_lst->str);
// 			temp_lst = get_temp_lst(symbol_lst->str);
// 			printf("2. %s\n", temp_lst->str);
// 			symbol_lst = lst_symbol_add_middle(symbol_lst, temp_lst);
// 			printf("3. %s\n", symbol_lst->str);
// 		}
// 		symbol_lst = symbol_lst->next;
// 	}
// 	symbol_lst = head->next;
// 	symbol_lst->pre = NULL;
// 	free(head->str);
// 	free(head);
// 	return (symbol_lst);
// }

/*-------------------------------------*/
