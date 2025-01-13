/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:14:00 by vdurand           #+#    #+#             */
/*   Updated: 2024/12/04 19:22:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

static int	handle_str(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1), 6);
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

static int	handle_pointer(void *p)
{
	size_t			pointer;
	size_t			lenght;

	pointer = (size_t)p;
	lenght = 0;
	if (!pointer)
		return (ft_putstr_fd("(nil)", 1), 5);
	ft_putstr_fd("0x", 1);
	lenght += 2;
	return (lenght + ft_putptr_fd(pointer, 1));
}

static int	process_arg(const char *format, size_t index, va_list ap)
{
	if (format[index] == '%')
		return (ft_putchar_fd('%', 1), 1);
	if (format[index] == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1), 1);
	if (format[index] == 's')
		return (handle_str(va_arg(ap, char *)));
	if (format[index] == 'p')
		return (handle_pointer(va_arg(ap, void *)));
	if (format[index] == 'd' || format[index] == 'i')
		return (ft_putnbr_base_fd(va_arg(ap, int), BASE_DECIMAL, 1));
	if (format[index] == 'u')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_DECIMAL, 1));
	if (format[index] == 'x')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_SMALL_HEX, 1));
	if (format[index] == 'X')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_BIG_HEX, 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	sum;
	size_t	i;

	if (!format)
		return (-1);
	va_start(ap, format);
	sum = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			sum += process_arg(format, i + 1, ap);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			sum++;
		}
		i++;
	}
	va_end(ap);
	return (sum);
}
// #include <limits.h>
// #include <stdio.h>

// int main()
// {
// 	ft_printf("%x\n", -10);
// 	printf("%x\n", -10);
// }
