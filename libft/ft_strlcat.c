/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:00 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:38:01 by minsukan         ###   ########.fr       */
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
