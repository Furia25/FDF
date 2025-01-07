/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:39:59 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/07 16:55:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	char	*last;

	chr = (char) c;
	last = NULL;
	while (*s != '\0')
	{
		if (*s == chr)
			last = (char *)s;
		s++;
	}
	if (chr == '\0')
		return ((char *) s);
	return (last);
}

/* 
int	main(void)
{
	char *test = "TEST1 ABCDEF";
	printf("%p\n", ft_strchr(test, '1'));
	printf("%p", test);
} */