/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:11:58 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/07 15:52:50 by jaehyuki         ###   ########.fr       */
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
