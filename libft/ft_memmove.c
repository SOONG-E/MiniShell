/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:26:48 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/15 21:53:50 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	movemem(unsigned char *temp,
					const unsigned char *srctemp,
					size_t len)
{
	int	i;

	if (temp <= srctemp)
	{
		i = 0;
		while ((unsigned int)i < len)
		{
			temp[i] = srctemp[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i >= 0)
		{
			temp[i] = srctemp[i];
			i--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*temp;
	const unsigned char	*srctemp;

	if (!dst && !src && len > 0)
		return (dst);
	temp = (unsigned char *)dst;
	srctemp = (unsigned char *)src;
	movemem(temp, srctemp, len);
	return (dst);
}
