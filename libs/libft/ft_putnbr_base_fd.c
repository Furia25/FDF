/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:45:44 by vdurand           #+#    #+#             */
/*   Updated: 2024/12/04 14:14:45 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int	ft_putnbr_base_fd(long nb, char *base, int fd)
{
	size_t		base_size;
	long long	nbr;
	int			length;

	length = 0;
	base_size = ft_strlen(base);
	nbr = (long long) nb;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
		length += 1;
	}
	if (nbr < (long)(base_size))
	{
		ft_putchar_fd(base[nbr], fd);
		return (length + 1);
	}
	else
	{
		length += ft_putnbr_base_fd(nbr / base_size, base, fd);
		ft_putchar_fd(base[nbr % base_size], fd);
		return (length + 1);
	}
}
/*int	main(void)
{
	char	b[] = "01";
	ft_putnbrr_base(10, b);
}*/
