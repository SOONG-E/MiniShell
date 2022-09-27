#include "./include/minishell.h"

char    *get_op(char *str)
{
    char    op_str[4];

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
    else 
        return (NULL);
    op_str[3] = '\0';
    return (ft_strdup(op_str));
}

char    *combine_str(char *s1, char *s2, char *s3, int *i)
{
    char    *ret;

    if (!s1 || !s2 || !s3)
        allocat_error();
    if (s2[1] == OP_AND_IF || s2[1] == OP_OR_IF
        || s2[1] == OP_IN_HEREDOC || s2[1] == OP_OUT_HEREDOC)
        *i += 2;
    else
        *i += 1;
    ret = ft_strjoin_free(ft_strjoin_free(s1, s2), s3);
    if (s2)
        free(s2);
    if (s3)
        free(s3);
    s1 = NULL;
    s2 = NULL;
    s3 = NULL;
    return (ret);
}

char    *preprocess_str(char *str)
{
    char    *ret;
    char    *op;
    int     i;

    ret = ft_strdup(str);
    i = 0;
    while (str[i])
    {
        if (str[i++] == '\"')
            i = ft_strichr(&str[i], '\"') + 1;
        if (str[i++] == '\'')
            i = ft_strichr(&str[i], '\'') + 1;
        op = get_op(&str[i]);
        if (op)
        {
            if (op[1] == OP_AND_IF || op[1] == OP_OR_IF
                || op[1] == OP_IN_HEREDOC || op[1] == OP_OUT_HEREDOC)
    			ret = combine_str(ft_substr(ret, 0, i), op, ft_strdup(&str[i + 2]), &i);
            else
    			ret = combine_str(ft_substr(ret, 0, i), op, ft_strdup(&str[i + 1]), &i);
        }
        else
            i++;
    }
    return (ret);
}