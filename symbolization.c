#include "./include/minishell.h"

char	*get_cmd_path(char *cmd, char *path)
{
	struct stat	sb;
	char		*rv_cmd;

	while (*path)
	{
		rv_cmd = ft_strjoin_free(ft_strjoin_free(ft_strndup(path,
						ft_strichr(path, ':')), "/"), cmd);
		if (!rv_cmd)
			allocat_error();
		if (stat(rv_cmd, &sb) >= 0)
			return (rv_cmd);
		free(rv_cmd);
		if (ft_strichr(path, ':') >= 0)
			path += ft_strichr(path, ':') + 1;
		else
			path += ft_strlen(path);
	}
	if (stat(cmd, &sb) >= 0)//built_in 명령어들 확인
		return (cmd);
	return (NULL);
}

int	is_cmd(char	*str)
{
	char	*path;
	char	*cmd_path;

	path = get_value_n("PATH", 4);
	cmd_path = get_cmd_path(str, path);
	free(path);
	if (cmd_path)
	{
		free(cmd_path);
		if (errno == ENOENT)
			return (0);
	}
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
	if (ft_strlen(str) != 1 || str[0] > 0)
		return (0);
	if (str[0] == OP_PIPE)
		return (T_PIPE);
	else if (str[0] == OP_OR_IF)
		return (T_OR_IF);
	else if (str[0] == OP_AND_IF)
		return (T_AND_IF);
	else if (str[0] == OP_IN_HEREDOC)
		return (T_IN_HEREDOC);
	else if (str[0] == OP_OUT_HEREDOC)
		return (T_OUT_HEREDOC);
	else if (str[0] == OP_LBRACE)
		return (T_LBRACE);
	else if (str[0] == OP_RBRACE)
		return (T_RBRACE);
	else if (str[0] == OP_IN_RID)
		return (T_IN_RID);
	else if (str[0] == OP_OUT_RID)
		return (T_OUT_RID);
	else
		return (0);
}

int	classify_type(t_symbol *symbols, int idx)
{
	int op;

	op = classify_operator(symbols[idx].str);
	if (op)
	{
		if (op == T_RBRACE)
			return (op);
		else if (symbols[idx + 1].str && classify_operator(symbols[idx + 1].str) == T_LBRACE)
			return (op);
		else if (symbols[idx + 1].str)
			symbols[idx + 1].type = (T_CMD + (op == T_IN_RID || op == T_OUT_RID));
		return (op);
	}
	else if (is_cmd(symbols[idx].str))
		return (T_CMD);
	else if (!ft_strcmp(symbols[idx].str, "-n"))
	{
		if (idx > 0 && (symbols[idx - 1].type == T_CMD || symbols[idx - 1].type == T_OPTION))
			return (T_OPTION);
	}
	else
		return (T_ARG);
	return (T_ARG);
}

void	put_type(t_symbol *symbols)
{
	int	idx;

	idx = -1;
	while (symbols[++idx].str)
	{
		if (symbols[idx].type < 0)
			symbols[idx].type = classify_type(symbols, idx);
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
		symbols[idx].str = ft_strdup(temp[idx]);
		symbols[idx].type = -1;
	}
	symbols[idx].str = 0;
	put_type(symbols);
	return (symbols);
}
