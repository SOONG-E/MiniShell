#include "./include/minishell.h"

char	*get_cmd_path(char *cmd, char *path)
{
	struct stat	sb;
	char		*rv_cmd;
	int			i;

	while (*path)
	{
		rv_cmd = ft_strjoin_free(ft_strjoin_free(ft_strndup(path,
						ft_strichr(path, ':')), "/"), cmd);
		if (!rv_cmd)
			allocat_error();
		if (stat(cmd, &sb) < 0)
			return (NULL);
		free(rv_cmd);
		if (ft_strichr(path, ':') >= 0)
			path += ft_strichr(path, ':') + 1;
		else
			path += ft_strlen(path);
	}
	if (stat(cmd, &sb));//built_in 명령어들 확인
		return (cmd);
}

int	is_cmd(char	*str)
{
	char	*path;

	path = get_value_n("PATH", 4);
	if (get_cmd_path(str, path) == NULL)
		if (errno == ENOENT)
			return (0);
	return (1);
}

int	count_amount(char **temp)
{
	int	count;

	count = 0;
	while (temp[count])
		++count;
	return (count);
}

int	classify_operator(char *str)
{
	if (strcmp(str, "|"))
		return (1);
	else if (strcmp(str, "||"))
		return (1);
	else if (strcmp(str, "&&"))
		return (1);
	else if (strcmp(str, "<<"))
		return (1);
	else if (strcmp(str, ">>"))
		return (1);
	else if (strcmp(str, "<"))
		return (2);
	else if (strcmp(str, ">"))
		return (2);
	else
		return (0);
}

int	classify_type(t_symbol **symbols, int idx)
{
	if (classify_operator((*symbols[idx]).str))
	{
		if ((*symbols[idx + 1]).str)
			(*symbols[idx + 1]).type = (T_CMD + (classify_operator((*symbols[idx]).str) == 2));
	}
	if (!strcmp((*symbols[idx]).str, "&&"))
		return (T_AND_IF);
	else if (!strcmp((*symbols[idx]).str, "||"))
		return (T_OR_IF);
	else if (!strcmp((*symbols[idx]).str, "|"))
		return (T_PIPE);
	else if ((*symbols[idx]).str[0] == '(' || (*symbols[idx]).str[0] == ')')
		return (T_LBRACE + ((*symbols[idx]).str[0] == ')'));
	else if (!strcmp((*symbols[idx]).str, "<<") || !strcmp((*symbols[idx]).str, ">>"))
		return (T_IN_HEREDOC + (strcmp((*symbols[idx]).str, ">>") == 0));
	else if ((*symbols[idx]).str[0] == '<' || (*symbols[idx]).str[0] == '>')
		return (T_IN_RID + ((*symbols[idx]).str[0] == '>'));
	else if (is_cmd((*symbols[idx]).str))
	{
		if ((*symbols[idx + 1]).str && (*symbols[idx + 1]).str[0] == '-')
			(*symbols[idx + 1]).type = T_OPTION;
		return (T_CMD);
	}
	else
		return (T_ARG);
}

void	put_type(t_symbol **symbols)
{
	int	idx;

	idx = -1;
	while ((*symbols[++idx]).str)
	{
		if ((*symbols[idx]).type < 0)
			(*symbols[idx]).type = classify_type(symbols, idx);
	}
}

t_symbol	*symbolizing(char **temp)
{
	t_symbol	*symbols;
	int			size;
	int			idx;

	size = count_amount(temp);
	symbols = (t_symbol *)ft_calloc((size + 1), sizeof(t_symbol));
	if (!symbols)
		allocat_error();
	idx = -1;
	while (++idx < size)
	{
		symbols[idx].str = temp[idx];
		symbols[idx].type = -1;
	}
	symbols[idx].str = 0;

}
