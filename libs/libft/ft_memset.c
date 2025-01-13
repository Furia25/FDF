/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:52:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/12 18:43:49 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*c_pointer;
	size_t			index;

	c_pointer = (unsigned char *) pointer;
	index = 0;
	while (index < count)
	{
		c_pointer[index] = (unsigned char) value;
		index++;
	}
	return (pointer);
}

/* int main () 
{
   char str[50];

   strcpy(str, "Welcome to Tutorialspoint");
   puts(str);

   ft_memset(str, '#', 7);
   puts(str);
   
   return(0);
} */