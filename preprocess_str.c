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
    if (s1)
        free(s1);
    if (s2)
        free(s2);
    if (s3)
        free(s3);
    s1 = NULL;
    s2 = NULL;
    s3 = NULL;
    return (ret);
}

int ft_skip_double_qoute(char *str)
{
    int i;
    
    i = 1;
    while (str[i] != Q_DOUBLE)
        i++;
    return (i + 1);
}

int ft_skip_single_qoute(char *str)
{
    int i;

    i = 1;
    while (str[i] != Q_SINGLE)
        i++;
    return (i + 1);
}

char    *preprocess_str(char *str)
{
    char    *op;
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == Q_DOUBLE)
            i += ft_skip_double_qoute(&str[i]);
        if (str[i] == Q_SINGLE)
            i += ft_skip_single_qoute(&str[i]);
        op = get_op(&str[i]);
        if (op)
        {
            if (op[1] == OP_AND_IF || op[1] == OP_OR_IF
                || op[1] == OP_IN_HEREDOC || op[1] == OP_OUT_HEREDOC)
    			str = combine_str(ft_substr(str, 0, i), op, ft_strdup(&str[i + 2]), &i);
            else
    			str = combine_str(ft_substr(str, 0, i), op, ft_strdup(&str[i + 1]), &i);
            i += 3;
        }
        else
            i++;
    }
    return (str);
}
