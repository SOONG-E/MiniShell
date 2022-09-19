/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:32:28 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/07 17:52:53 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	len_src;
	unsigned int	len_dst;

	len_src = ft_strlen((char *)src);
	len_dst = ft_strlen(dst);
	if (dstsize < len_dst)
		return (len_src + dstsize);
	i = 0;
	while (*dst)
	{
		dst++;
	}
	while (*src && len_dst + i + 1 < dstsize)
	{
		*dst++ = *src++;
		i++;
	}
	*dst = '\0';
	return (len_dst + len_src);
}
