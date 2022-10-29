/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:36:52 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:36:54 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*rv;

	rv = (unsigned char *)b;
	i = 0;
	while (i < len)
		rv[i++] = (unsigned char)c;
	return (rv);
}
