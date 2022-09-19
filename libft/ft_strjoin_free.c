/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:38:07 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/07 20:27:37 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
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
		return (NULL);
	ft_memcpy(rv, s1, len_s1);
	ft_strlcpy(rv + len_s1, (char *)s2, len_s2 + 1);
	if (s1)
	{
		free((char *)s1);
		s1 = NULL;
	}
	return (rv);
}
