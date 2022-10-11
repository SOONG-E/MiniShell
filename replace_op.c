#include "./include/minishell.h"

static char	*combine_str(char *s1, char *s2, char *s3, int *i);
static char	*get_op(char *str);
static int	get_num(char c);
static int	skip(char *line, int flag);

char	*replace_op(char *line)
{
	char	*op;
	char	*tmp;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == Q_DOUBLE || line[i] == Q_SINGLE)
			i += skip(&line[i], line[i]);
		op = get_op(&line[i]);
		if (op)
		{
			tmp = line;
			line = combine_str(ft_substr(line, 0, i), op, \
			ft_strdup(&line[i + get_num(op[1])]), &i);
			free(tmp);
			i += 2;
		}
		else
			i++;
	}
	return (line);
}

static char	*combine_str(char *s1, char *s2, char *s3, int *i)
{
	char	*str;
	char	*tmp;

	if (s2[1] == OP_IN_HEREDOC || s2[1] == OP_OUT_HEREDOC || \
	s2[1] == OP_AND_IF || s2[1] == OP_OR_IF)
		*i += 2;
	else
		*i += 1;
	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	free(s1);
	free(s2);
	free(s3);
	return (str);
}

static int	get_num(char c)
{
	if (c == OP_IN_HEREDOC || c == OP_OUT_HEREDOC || \
	c == OP_AND_IF || c == OP_OR_IF)
		return (2);
	else
		return (1);
}

static int	skip(char *line, int flag)
{
	char	*tmp;

	tmp = line;
	line++;
	if (flag == Q_DOUBLE)
	{
		while (*line && *line != Q_DOUBLE)
			line++;
		return (line - tmp);
	}
	else
	{
		while (*line && *line != Q_SINGLE)
			line++;
		return (line - tmp);
	}
}

static char	*get_op(char *str)
{
	char	op_str[4];

	op_str[0] = ' ';
	op_str[2] = ' ';
	if (!ft_strncmp(str, "<<", 2))
		op_str[1] = OP_IN_HEREDOC;
	else if (!ft_strncmp(str, ">>", 2))
		op_str[1] = OP_OUT_HEREDOC;
	else if (!ft_strncmp(str, "||", 2))
		op_str[1] = OP_OR_IF;
	else if (!ft_strncmp(str, "&&", 2))
		op_str[1] = OP_AND_IF;
	else if (!ft_strncmp(str, "<", 1))
		op_str[1] = OP_IN_RID;
	else if (!ft_strncmp(str, ">", 1))
		op_str[1] = OP_OUT_RID;
	else if (!ft_strncmp(str, "|", 1))
		op_str[1] = OP_PIPE;
	else if (!ft_strncmp(str, "(", 1))
		op_str[1] = OP_LBRACE;
	else if (!ft_strncmp(str, ")", 1))
		op_str[1] = OP_RBRACE;
	else
		return (NULL);
	op_str[3] = '\0';
	return (ft_strdup(op_str));
}






















// char	*replace_op(char *str)
// {
// 	char	*op;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		op = get_op(&str[i]);
// 		if (str[i] == Q_DOUBLE || str[i] == Q_SINGLE)
// 			i += ft_skip_qoute(&str[i], str[i]);
// 		else if (op)
// 		{
// 			temp = str;
// 			if (op[1] == OP_AND_IF || op[1] == OP_OR_IF
// 				|| op[1] == OP_IN_HEREDOC || op[1] == OP_OUT_HEREDOC)
// 				str = combine_str(ft_substr(str, 0, i), op, ft_strdup(&str[i + 2]), &i);
// 			else
// 				str = combine_str(ft_substr(str, 0, i), op, ft_strdup(&str[i + 1]), &i);
// 			free(temp);
// 			i += 2;
// 		}
// 		else
// 			i++;
// 	}
// 	return (str);
// }

// static int	ft_skip_quote(char *str, int flag)
// {
// 	int	i;

// 	i = 1;
// 	if (flag == Q_SINGLE)
// 	{
// 		while (str[i] != Q_SINGLE)
// 			i++;
// 		return (i + 1);
// 	}
// 	else if (flag == Q_DOUBLE)
// 	{
// 		while (str[i] != Q_DOUBLE)
// 			i++;
// 		return (i + 1);
// 	}
// }

// static void	replace_backup(char	**temp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (temp[i])
// 	{
// 		j = 0;
// 		while (temp[i][j])
// 		{
// 			if (temp[i][j] < 0 && temp[i][j] > -40)
// 				temp[i][j] *= -1;
// 			j++;
// 		}
// 		i++;
// 	}
// }
// static char	*combine_str(char *s1, char *s2, char *s3, int *i)
// {
// 	char	*ret;

// 	if (!s1 || !s2 || !s3)
// 		allocat_error();
// 	if (s2[1] == OP_AND_IF || s2[1] == OP_OR_IF
// 		|| s2[1] == OP_IN_HEREDOC || s2[1] == OP_OUT_HEREDOC)
// 		*i += 2;
// 	else
// 		*i += 1;
// 	ret = ft_strjoin_free(ft_strjoin(s1, s2), s3);
// 	if (s1)
// 		free(s1);
// 	if (s2)
// 		free(s2);
// 	if (s3)
// 		free(s3);
// 	return (ret);
// }

//
