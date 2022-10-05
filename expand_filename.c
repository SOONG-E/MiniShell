#include "./include/minishell.h"


void	replace_quote(char *str)
{
	while (*str)
	{
		if (*str == Q_DOUBLE)
		{
			str++;
			while (*str != Q_DOUBLE)
			{
				if (*str == Q_SINGLE)
					*str *= -1;
				str++;
			}
		}
		if (*str == Q_SINGLE)
		{
			str++;
			while (*str != Q_SINGLE)
			{
				if (*str == Q_DOUBLE)
					*str *= -1;
				str++;
			}
		}
		str++;
	}
}

int	quote_cnt(char *str)
{
	int	i;

	i = 0;
	while (*str++)
	{
		if (*str == Q_DOUBLE || *str == Q_SINGLE)
			i++;
	}
	return (i);
}

t_symbol	*delete_quote(t_symbol *symbol)
{
	char	*tmp;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	replace_quote(symbol->str);
	tmp = (char *)ft_calloc(ft_strlen(symbol->str) - quote_cnt(symbol->str) + 1, 1);
	while (symbol->str[i++] != 0)
	{
		if (symbol->str[i] != Q_SINGLE && symbol->str[i] != Q_DOUBLE)
			tmp[j++] = symbol->str[i];
	}
	free(symbol->str);
	symbol->str = tmp;
}

int	is_need_expand(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i++] == Q_SINGLE)
			i += ft_strichr(&str[i], Q_SINGLE) + 1;//??
		else if (str[i++] == Q_DOUBLE)
			i += ft_strichr(&str[i], Q_DOUBLE) + 1;
		else if (str[i] == '*')
			return (1);
		else
			i++;
	}
	return (0);
}

t_symbol	*get_file_lst(t_symbol *symbol)
{
	t_symbol		*file_lst;
	DIR				*dirp;
	struct dirent	*file_entry;

	dirp = opendir('.');
	file_entry = readdir(dirp);
	while (file_entry)
	{
		printf("%s", file_entry->d_name);
		file_entry = readdir(dirp);
	}
	return (NULL);
}

t_symbol	*expand_filename(t_symbol *symbol)
{
	t_symbol	*ret_symbol;
	t_symbol	*file_lst;

	ret_symbol = symbol;
	while (symbol)
	{
		if (symbol->type == T_FILEPATH || symbol->type == T_ARG)
		{
			if (is_need_expand(symbol->str))
			{
				file_lst = get_file_lst(symbol);
				symbol = lst_symbol_add_middle(symbol, file_lst);
			}
			else
				delete_quote(symbol);
		}
		symbol = symbol->next;
	}

	return (ret_symbol);
}