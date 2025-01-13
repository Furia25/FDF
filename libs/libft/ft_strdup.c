/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:54:13 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/07 17:28:09 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*temp;
	size_t	index;
	size_t	size;

	size = ft_strlen(s);
	temp = (char *)malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	index = 0;
	while (s[index])
	{
		temp[index] = s[index];
		index++;
	}
	temp[index] = '\0';
	return (temp);
}
