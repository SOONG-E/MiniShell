/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:23:40 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/07 14:37:17 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char			*rv;
	unsigned int	i;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	if (i < n)
		rv = (char *)malloc(i * sizeof(char) + 1);
	else
		rv = (char *)malloc(n * sizeof(char) + 1);
	if (!rv)
		return (NULL);
	i = 0;
	while (i < n && s1[i])
	{
		rv[i] = s1[i];
		i++;
	}
	rv[i] = '\0';
	return (rv);
}
