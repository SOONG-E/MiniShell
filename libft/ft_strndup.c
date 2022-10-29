/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:24 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:38:26 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char			*rv;
	unsigned int	i;

	if (!s1)
		exit(1);
	i = 0;
	while (s1[i])
		i++;
	if (i < n)
		rv = (char *)malloc(i * sizeof(char) + 1);
	else
		rv = (char *)malloc(n * sizeof(char) + 1);
	if (!rv)
		exit(1);
	i = 0;
	while (i < n && s1[i])
	{
		rv[i] = s1[i];
		i++;
	}
	rv[i] = '\0';
	return (rv);
}
