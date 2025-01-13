/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:31:45 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/13 13:35:37 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

int	ft_lstsize(t_list *lst)
{
	if (!lst)
		return (0);
	if (lst -> next != NULL)
		return (1 + ft_lstsize(lst -> next));
	return (1);
}

/* int	main(void)
{
	t_list *test = ft_lstnew(ft_strdup("test"));
	t_list *test2 = ft_lstnew(ft_strdup("test"));
} */