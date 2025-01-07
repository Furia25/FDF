/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:46:41 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/07 16:17:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*o_s;

	o_s = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (o_s[index] == (unsigned char) c)
			return ((void *)s + index);
		index++;
	}
	return (NULL);
}
