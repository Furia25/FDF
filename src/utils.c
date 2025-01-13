/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:44:13 by val               #+#    #+#             */
/*   Updated: 2025/01/12 18:47:19 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>

void	*memset_fast(void* ptr, int value, size_t num)
{
    unsigned char	*p;
    unsigned char	val;

	val = (unsigned char)value;
	p = ptr;
    while (((uintptr_t)p & 7) && num--)
        *p++ = val;
    uint64_t val64 = (uint64_t)val | ((uint64_t)val << 8) |
                     ((uint64_t)val << 16) | ((uint64_t)val << 24) |
                     ((uint64_t)val << 32) | ((uint64_t)val << 40) |
                     ((uint64_t)val << 48) | ((uint64_t)val << 56);
    while (num >= 8)
	{
        *(uint64_t*)p = val64;
        p += 8;
        num -= 8;
    }
    while (num--)
        *p++ = val;
    return (ptr);
}