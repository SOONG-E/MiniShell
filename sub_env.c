#include "./include/minishell.h"

char	*get_value_n(char *key, int n)
{
	t_envlst	*temp;
	
	temp = g_envlst;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, n))
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

char	*delete_quote(char *str)
{
	char	*ret;
	int		idx1;
	int		idx2;

	if (str[0] != '\'' && str[0] != '\"')
		return (str);
	ret = (char *)malloc((ft_strlen(str) - 1) * sizeof(char));
	if (!ret)
		allocat_error();
	idx1 = 0;
	idx2 = 1;
	while (idx2 < (int)ft_strlen(str) - 1)
		ret[idx1++] = str[idx2++];
	ret[idx1] = 0;
	free(str);
	return (ret);
}

char	*finding_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		++i;
	if (i == 0)
		ret = ft_strjoin("$", &str[i]);
	else if (get_value_n(str, i))
		ret = ft_strjoin(get_value_n(str, i), &str[i]);
	else
		ret = ft_strdup(&str[i]);
	if(!ret)
		allocat_error();
	free(str);
	return (ret);
}

char	*expand_env(char *str)
{
	int 	i;
	char	**temp;
	char 	*ret;

	temp = ft_split(str, "$");
	/////////////////////

	if (!temp)
		allocat_error();
	if (str[0] == '$')
		temp[0] = finding_env(temp[0]);
	i = 0;
	while (temp[++i])
		temp[i] = finding_env(temp[i]);
	i = 0;
	while (temp[++i])
		temp[0] = ft_strjoin_free(temp[0], temp[i]);
	//free
	ret = temp[0];
	return (ret); //수정
}

void	sub_env(char **temp)
{
	int	i;

	i = -1;
	while (temp[++i])
	{
		if (temp[i][0] == '\'')
			temp[i] = delete_quote(temp[i]);			//if not single quote
		else
		{
			temp[i] = delete_quote(temp[i]);
			temp[i] = expand_env(temp[i]);
		}
        printf("%sEND\n", temp[i]);		//if single quote
	}
}
