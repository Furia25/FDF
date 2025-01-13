/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:56:55 by abetemps          #+#    #+#             */
/*   Updated: 2024/11/07 15:56:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	i = 0;
	if (size > dest_len)
	{
		while ((src[i]) && (i < size - 1 - dest_len))
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[dest_len + i] = '\0';
		return (dest_len + src_len);
	}
	return (src_len + size);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	unsigned int	n;
	n = 9;
	char dest[200] = "Yo";
	char *src = "la team";
	printf("New function : %d\n", ft_strlcat(dest, src, n));
	printf("New function : %s\n", dest);
	char desti[200] = "Yo";
	char sourc[] = "la team";
	printf("Real function : %zu\n", strlcat(desti, sourc, n));
	printf("Real function : %s\n", desti);
	return (0);
}
*/
