/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:21:56 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/08 18:23:37 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*rv_lst;

	rv_lst = (t_list *)malloc(sizeof(t_list));
	if (!(rv_lst))
		return (NULL);
	rv_lst -> content = content;
	rv_lst -> next = 0;
	return (rv_lst);
}
