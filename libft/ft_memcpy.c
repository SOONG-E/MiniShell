/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:13:47 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/15 21:34:57 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*rv;
	unsigned char	*temp;

	if (!dst && !src && n > 0)
		return (dst);
	rv = (unsigned char *)dst;
	temp = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		rv[i] = (unsigned char)temp[i];
		i++;
	}
	return (rv);
}
