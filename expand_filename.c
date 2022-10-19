#include "minishell.h"

int	is_need_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == Q_SINGLE)
		{
			i++;
			i += ft_strichr(&str[i], Q_SINGLE) + 1;
		}
		else if (str[i] == Q_DOUBLE)
		{
			i++;
			i += ft_strichr(&str[i], Q_DOUBLE) + 1;
		}
		else if (str[i] == '*')
			return (1);
		else
			i++;
	}
	return (0);
}

static int	name_check(char *filename, char *wild, char **wild_card)
{
	int	file_name_len;
	int	i;

	file_name_len = ft_strlen(filename);
	i = 0;
	while (wild_card[i])
	{
		filename = ft_strnstr(filename, wild_card[i], file_name_len);
		if (!filename)
			return (0);
		i++;
	}
	if (*(filename + ft_strlen(wild_card[i - 1]))
		&& wild[ft_strlen(wild) - 1] != '*')
		i = 0;
	else
		i = 1;
	return (i);
}

int	cmp_wild_card(char *filename, char *wild)
{
	char	**wild_cards;

	wild_cards = ft_split(wild, "*");
	if (wild_cards[0] == NULL)
		return (1);
	replace_back_wild_card(wild_cards);
	if (wild[0] != '*'
		&& ft_strncmp(filename, wild_cards[0], ft_strlen(wild_cards[0])) != 0)
		return (0);
	if (name_check(filename, wild, wild_cards) == 0)
		return (0);
	return (1);
}

t_symbol	*get_file_lst(t_symbol *symbol)
{
	t_symbol		*file_lst;
	t_symbol		*file;
	DIR				*dirp;
	struct dirent	*file_entry;

	file_lst = NULL;
	dirp = opendir(".");
	file_entry = readdir(dirp);
	file_entry = readdir(dirp);
	file_entry = readdir(dirp);
	while (file_entry)
	{
		if (cmp_wild_card(file_entry->d_name, symbol->str))
		{
			file = new_symbol(file_entry->d_name);
			file->type = symbol->type;
			add_back_symbol(&file_lst, file);
		}
		file_entry = readdir(dirp);
	}
	closedir(dirp);
	return (file_lst);
}

void	expand_filename(t_symbol *symbol)
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
				replace_wild_card(symbol->str);
				delete_quote(symbol);
				file_lst = get_file_lst(symbol);
				if (file_lst)
					symbol = update_symbol(symbol, file_lst);
				else
					symbol = symbol->next;
			}
			else
			{
				delete_quote(symbol);
				symbol = symbol->next;
			}
		}
		else
			symbol = symbol->next;
	}
}
