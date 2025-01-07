/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:31:45 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/13 11:51:08 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next != NULL)
		return (ft_lstlast(lst -> next));
	return (lst);
}

/* int	main(void)
{
	t_list *test = ft_lstnew(ft_strdup("test"));
	t_list *test2 = ft_lstnew(ft_strdup("test"));
} */