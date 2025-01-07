/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:29:08 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/08 18:11:05 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *l, size_t len)
{
	size_t	i;
	size_t	is;
	size_t	size;

	if (!*l)
		return ((char *) big);
	size = ft_strlen(l);
	i = 0;
	while (big[i] && i < len)
	{
		is = 0;
		while (big[i + is] == l[is] && l[is] && i + is < len)
		{
			is++;
			if (is == size)
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char *test = "aaxx";
	char *search = "xx";
	printf("%p\n", ft_strnstr(test, search, 4));
	printf("%p", test);
} */