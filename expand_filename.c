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

static int	name_check(char *filename, int len, char **wild_card, int *idx)
{
	while (wild_card[*idx])
	{
		filename = ft_strnstr(filename, wild_card[*idx], len);
		if (!filename)
			return (0);
		(*idx)++;
	}
	return (1);
}

int	cmp_wild_card(char *filename, char *wild)
{
	int		i;
	int		len_filename;
	char	**wild_cards;

	i = 0;
	len_filename = ft_strlen(filename);
	wild_cards = ft_split(wild, "*");
	if (wild_cards[0] == NULL)
		return (1);
	replace_back_wild_card(wild_cards);
	if (wild[0] != '*'
		&& ft_strncmp(filename, wild_cards[0], ft_strlen(wild_cards[0])) != 0)
		return (0);
	if (name_check(filename, len_filename, wild_cards, &i) == 0)
	{
		split_free(wild_cards);
		return (0);
	}
	if (*(filename + ft_strlen(wild_cards[i - 1]))
		&& wild[ft_strlen(wild) - 1] != '*')
		i = 0;
	else
		i = 1;
	printf("%d\n\n", i);
	split_free(wild_cards);
	return (i);
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
		printf("%s\n\n ", symbol->str);
		printf("%s\n\n", file_entry->d_name);
		if (cmp_wild_card(file_entry->d_name, symbol->str))
		{
			printf("%s\n\n", file_entry->d_name);
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
				///
				printf("%p\n\n", file_lst);
				t_symbol	*temp = file_lst;
				while (temp)
				{
					printf("%s ", temp->str);
					temp = temp->next;
				}
				///
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
