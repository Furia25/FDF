/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:08:22 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/07 15:56:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*o_dest;
	unsigned char	*o_src;

	if (dest == src)
		return (dest);
	if (dest > src)
	{
		o_dest = (unsigned char *) dest + n - 1;
		o_src = (unsigned char *) src + n - 1;
		while (n--)
			*o_dest-- = *o_src--;
	}
	else
	{
		o_dest = (unsigned char *) dest;
		o_src = (unsigned char *) src;
		while (n--)
			*o_dest++ = *o_src++;
	}
	return (dest);
}
