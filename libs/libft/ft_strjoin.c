/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:25:15 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/14 15:17:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	index;
	size_t	pre_size;

	if (!s1 || !s2)
		return (NULL);
	pre_size = ft_strlen(s1);
	temp = (char *)malloc(sizeof(char) * (pre_size + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	index = 0;
	while (s1[index])
	{
		temp[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index])
	{
		temp[pre_size + index] = s2[index];
		index++;
	}
	temp[pre_size + index] = '\0';
	return (temp);
}

/* int	main(void)
{
	printf(ft_strjoin("gfg", " ouiiiiii"));
} */
