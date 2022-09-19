/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:21:31 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/08 20:22:05 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rv;
	t_list	*temp;

	if (!lst)
		return (NULL);
	rv = ft_lstnew(f(lst -> content));
	if (!(rv))
		return (NULL);
	temp = rv;
	lst = lst -> next;
	while (lst)
	{
		temp -> next = ft_lstnew(f(lst -> content));
		if (!(temp -> next))
		{
			ft_lstclear(&rv, del);
			return (NULL);
		}
		temp = temp -> next;
		lst = lst -> next;
	}
	return (rv);
}
