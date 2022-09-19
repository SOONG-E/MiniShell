/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:42 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/15 20:05:43 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (c);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*rv;
	size_t			len_rv;
	unsigned int	start;
	unsigned int	end;

	if (!s1)
		return (NULL);
	start = 0;
	while (is_set(s1[start], set))
		start++;
	if (ft_strlen((char *)s1) == 0)
		end = 0;
	else
		end = ft_strlen((char *)s1) - 1;
	while (is_set(s1[end], set) && end > start)
		end--;
	if (end - start < 0)
		return (ft_strdup(""));
	len_rv = end - start + 1;
	rv = (char *)malloc(len_rv * sizeof(char) + 1);
	if (!rv)
		return (NULL);
	ft_strlcpy(rv, s1 + start, len_rv + 1);
	return (rv);
}
