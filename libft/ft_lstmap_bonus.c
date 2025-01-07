/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:33:35 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/25 13:07:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del) (void *))
{
	t_list	*n_node;
	t_list	*n_lst;
	void	*pt;

	n_lst = NULL;
	while (lst)
	{
		pt = f(lst->content);
		if (!pt)
		{
			ft_lstclear(&n_lst, del);
			return (NULL);
		}
		n_node = ft_lstnew(pt);
		if (!n_node)
		{
			if (del)
				del(pt);
			ft_lstclear(&n_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&n_lst, n_node);
		lst = lst->next;
	}
	return (n_lst);
}
