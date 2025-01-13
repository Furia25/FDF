/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:58:20 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/07 16:35:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*o_s1;
	unsigned char	*o_s2;

	o_s1 = (unsigned char *)s1;
	o_s2 = (unsigned char *)s2;
	while (n)
	{
		if (*o_s1 != *o_s2)
			return (*o_s1 - *o_s2);
		o_s1++;
		o_s2++;
		n--;
	}
	return (0);
}

/*  int	main(void)
{
	char *test = "";
	char *test2 = "";
	
	printf("%d\n", memcmp((void *)test, (void *)test2, 25));
	printf("%d", ft_memcmp((void *)test, (void *)test2, 25));
}  */