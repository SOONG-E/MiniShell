/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:36:39 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:36:41 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	if ((s1_temp == 0 && s2_temp == 0) || n == 0)
		return (0);
	while (n > 0)
	{
		if (*s1_temp != *s2_temp)
			return (*s1_temp - *s2_temp);
		s1_temp++;
		s2_temp++;
		n--;
	}
	return (0);
}
