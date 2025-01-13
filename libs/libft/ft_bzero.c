/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:35:28 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/07 16:23:47 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*o;

	o = (unsigned char *) s;
	while (n)
	{
		*o = 0;
		o++;
		n--;
	}
}

/* int	main(void)
{
	char test[50];
	test[2] = '\0';
	test[5] = '\0';
	ft_bzero(&test, 50);
	printf(test);
} */