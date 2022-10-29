/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:37:39 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:37:40 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*rv;
	unsigned int	i;

	i = 0;
	while (s1[i])
		i++;
	rv = (char *)malloc(i * sizeof(char) + 1);
	if (!rv)
		exit(1);
	i = 0;
	while (s1[i])
	{
		rv[i] = s1[i];
		i++;
	}
	rv[i] = '\0';
	return (rv);
}
