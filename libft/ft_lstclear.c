/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:24:27 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/07/08 19:24:53 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next_lst;

	if (!lst)
		return ;
	temp = *lst;
	while (temp)
	{
		next_lst = temp -> next;
		ft_lstdelone(temp, del);
		temp = next_lst;
	}
	lst[0] = NULL;
}
