/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:14 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:38:16 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rv;
	int		i;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen((char *)s);
	rv = (char *)malloc(len_s * sizeof(char) + 1);
	if (!rv)
		exit(1);
	i = 0;
	while (i < (int)len_s)
	{
		rv[i] = f(i, s[i]);
		i++;
	}
	rv[i] = '\0';
	return (rv);
}
