#include "minishell.h"

// char	**double_quote_split(char *str, char chr);

// static char	*simple_join_three_str(char *str1, char *str2, char *str3)
// {
// 	char	*ret;

// 	ret = ft_strjoin(str1, str2);
// 	ret = ft_strjoin_free(ret, str3);
// 	free(str1);
// 	free(str2);
// 	free(str3);
// 	return (ret);
// }

// static char	*find_env(char *str)
// {
// 	int		i;
// 	char	*ret;

// 	if (str[0] == '?')
// 	{
// 		ret = ft_strjoin(g_info->exit_code, &str[1]); // exitcode 따로 환경변수 만들어야하는지? 일단 set_envlst만들뒀어ㅡㅂ네다
// 		free(str);
// 		return (ret);
// 	}
// 	i = 0;
// 	while (ft_isalnum(str[i]) || str[i] == '_')
// 		++i;
// 	if (i == 0)
// 		ret = ft_strjoin("$", &str[i]);
// 	else
// 		ret = ft_strjoin_free(get_value_n(str, i), &str[i]);
// 	free(str);
// 	return (ret);
// }

// static char	*expand_env_in_quote(char *str)
// {
// 	int		i;
// 	char	**temp;
// 	char	*ret;

// 	temp = double_quote_split(str, '$');
// 	if (!temp)
// 		allocat_error();
// 	free(str);
// 	i = 0;
// 	while (temp[++i])
// 		temp[i] = find_env(temp[i]);
// 	i = 0;
// 	while (temp[++i])
// 	{
// 		temp[0] = ft_strjoin_free(temp[0], temp[i]);
// 		if (!temp[0])
// 			allocat_error();
// 	}
// 	ret = ft_strdup(temp[0]);
// 	if (!ret)
// 		allocat_error();
// 	split_free(temp);
// 	return (ret);
// }

// static char	*env_split_merge(char *str, int *i)
// {
// 	char	**temp;
// 	int		j;

// 	temp = (char **)malloc(3 * sizeof(char *));
// 	if (!temp)
// 		allocat_error();
// 	temp[0] = ft_substr(str, 0, *i);
// 	j = *i + 1;
// 	while (str[j] != Q_DOUBLE)
// 			++j;
// 	temp[1] = expand_env_in_quote(ft_substr(str, *i, j - *i + 1));
// 	temp[2] = ft_substr(str, j + 1, ft_strlen(str) - j - 1);
// 	free(str);
// 	str = simple_join_three_str(temp[0], temp[1], temp[2]);
// 	*i += (ft_strichr(&str[*i + 1], Q_DOUBLE) + 2);
// 	free(temp);
// 	return (str);
// }

// char	*expand_env_quote_case(char *str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == Q_SINGLE)
// 			i += (ft_strichr(&str[i + 1], Q_SINGLE) + 2);
// 		else if (str[i] == Q_DOUBLE)
// 			str = env_split_merge(str, &i);
// 		else
// 			++i;
// 	}
// 	return (str);
// }

/*-------------------------------------------*/
