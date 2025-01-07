/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:15:48 by vdurand           #+#    #+#             */
/*   Updated: 2024/12/04 14:17:01 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_putptr_fd(size_t ptr, int fd)
{
	int	length;

	length = 0;
	if (ptr < 16)
	{
		ft_putchar_fd(BASE_SMALL_HEX[ptr], fd);
		return (length + 1);
	}
	else
	{
		length += ft_putptr_fd(ptr / 16, fd);
		ft_putchar_fd(BASE_SMALL_HEX[ptr % 16], fd);
		return (length + 1);
	}
}
