/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:38:24 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/15 21:47:11 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_str_c(char const *s, char c, int *i)
{
	int	j;

	j = 0;
	if (s[*i] == c)
		while (s[*i] == c)
			i[0]++;
	while (s[*i + j] != c && s[*i + j])
		j++;
	return (j);
}

static int	count_strs(char const *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
		}
		else
		{
			cnt++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (cnt);
}

static unsigned int	split_strlcpy(char *dst,
						const char *src,
						size_t dstsize,
						char c)
{
	unsigned int	len_src;
	unsigned int	i;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	len_src = i;
	i = 0;
	while (i + 1 < dstsize && src[i] && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (len_src);
}

static char	**free_all(int i, char **rv)
{
	i--;
	while (i >= 0)
	{
		free(rv[i]);
		rv[i] = NULL;
		i--;
	}
	free(rv);
	rv = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**rv;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	rv = (char **)malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (!rv)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_strs(s, c))
	{
		rv[j] = (char *)malloc(len_str_c(s, c, &i) * sizeof(char) + 1);
		if (!rv[j])
			return (free_all(j, rv));
		i += split_strlcpy(&rv[j++][0], &s[i], len_str_c(s, c, &i) + 1, c);
	}
	rv[j] = 0;
	return (rv);
}
