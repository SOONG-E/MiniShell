/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:35:56 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:35:58 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*rv;
	unsigned int	i;

	rv = (unsigned char *)s;
	i = 0;
	while (i < n)
		rv[i++] = 0;
}
