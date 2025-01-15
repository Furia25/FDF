/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:33:39 by val               #+#    #+#             */
/*   Updated: 2025/01/15 21:48:01 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strend(char *str, char *suffix)
{
	size_t	str_len;
	size_t	suffix_len;

	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (!str || !suffix)
		return (0);
	if (suffix_len > str_len)
		return (0);
	return (ft_strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0);
}
