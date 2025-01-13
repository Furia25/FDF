/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:59:40 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/13 11:06:15 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	tmin(size_t m1, size_t m2)
{
	if (m1 > m2)
		return (m2);
	return (m1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	index;
	size_t	size;

	index = 0;
	size = ft_strlen(s);
	if (start >= size || s == NULL || len <= 0)
		return (ft_calloc(1, sizeof(char)));
	result = (char *)malloc(sizeof(char) * (tmin(size - start, len) + 1));
	if (!result)
		return (NULL);
	while (s[start + index] && index < len)
	{
		result[index] = s[start + index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

/*   int	main(void)
{
	char *test = "je suis";
	char *result;
	
	result = ft_substr(test, 2, 8);
	//printf(test);
	printf("%s", result);
	free(result);	
} */