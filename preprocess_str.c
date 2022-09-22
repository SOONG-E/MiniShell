#include "./include/minishell.h"

int op_check(char *str)
{
    if (!ft_strncmp(str, "<<", 2) == 0 || !ft_strncmp(str, ">>", 2))
}

char    *preprocess_str(char *str)
{
    char    **temp;
    char    *temp_str;
    int     i;

    i = 0;
    temp_str = str;
    while (str[i])
    {
        if (str[i++] == '/"')
            i = ft_strichr(&str[i], '\"') + 1;
        if (str[i++] == '\'')
            i = ft_strichr(&str[i], '\'') + 1;
        if (op_check(&str[i]))
        {
            
        }
        else
            i++;
        
    }
    
    
}