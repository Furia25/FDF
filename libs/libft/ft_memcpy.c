/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:08:22 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/25 21:00:50 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*o_dest;
	unsigned char	*o_src;
	size_t			index;

	index = 0;
	o_dest = (unsigned char *) dest;
	o_src = (unsigned char *) src;
	while (index < n)
	{
		o_dest[index] = o_src[index];
		index++;
	}
	return (dest);
}

/* int	main(void)
{
	char test[50];
	char *test2 = "TEST";

	ft_memcpy(&test, test2, 4);
	printf(test);
} */