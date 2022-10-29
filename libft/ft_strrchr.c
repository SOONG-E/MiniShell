/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:33 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:38:34 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	if (c > 256)
		c %= 256;
	while (*s)
		s++;
	while (temp != s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	if (*temp == c || c == '\0')
		return (temp);
	else
		return (0);
}
