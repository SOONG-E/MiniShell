/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:37:56 by minsukan          #+#    #+#             */
/*   Updated: 2022/10/29 19:37:57 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*rv;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	rv = (char *)malloc((len_s1 + len_s2) * sizeof(char) + 1);
	if (!rv)
		exit(1);
	ft_memcpy(rv, s1, len_s1);
	ft_strlcpy(rv + len_s1, (char *)s2, len_s2 + 1);
	return (rv);
}
