/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:09:26 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/22 15:34:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t el_count, size_t el_size)
{
	void	*temp;
	size_t	size;

	if (el_size == 0 || el_count == 0)
		return (malloc(0));
	if (el_count > __SIZE_MAX__ / el_size \
		|| el_size > __SIZE_MAX__ / el_count)
		return (NULL);
	size = el_count * el_size;
	temp = malloc(size);
	if (!temp)
		return (NULL);
	ft_memset(temp, 0, size);
	return (temp);
}

/* int	main(void)
{
	char	*test;

	test = (char *)ft_calloc(50, sizeof(char));
	test[0] = 'b';
	test[1] = 'o';
	test[2] = 'o';
	test[3] = 'o';
	printf(test);
} */