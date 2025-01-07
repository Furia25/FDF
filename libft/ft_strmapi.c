/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:55:52 by vdurand           #+#    #+#             */
/*   Updated: 2024/11/08 13:25:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*temp;
	size_t	size;
	size_t	index;

	size = ft_strlen(s);
	temp = (char *)malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	index = 0;
	while (s[index])
	{
		temp[index] = (*f)(index, s[index]);
		index++;
	}
	temp[index] = '\0';
	return (temp);
}
