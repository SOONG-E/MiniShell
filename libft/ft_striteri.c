/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:37:48 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:37:49 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	size_t			len_s;

	if (!s)
		return ;
	len_s = ft_strlen((char *)s);
	i = 0;
	while (i < (unsigned int)len_s)
	{
		f(i, &s[i]);
		i++;
	}
}
