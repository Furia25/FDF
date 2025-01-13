/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:46:46 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/07 16:30:32 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(size_t, char *))
{
	size_t	index;

	index = 0;
	while (s[index])
	{
		(*f)(index, s + index);
		index++;
	}
}
