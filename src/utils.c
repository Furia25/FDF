/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:44:13 by val               #+#    #+#             */
/*   Updated: 2025/01/14 15:56:41 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>

void	*memset_fast(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	val;
	uint64_t		val64;

	val = (unsigned char)value;
	p = ptr;
	while (((uintptr_t)p & 7) && num--)
		*p++ = val;
	val64 = (uint64_t)val | ((uint64_t)val << 8) | ((uint64_t)val << 16) \
	| ((uint64_t)val << 24) | ((uint64_t)val << 48) | ((uint64_t)val << 56);
	while (num >= 8)
	{
		*(uint64_t *)p = val64;
		p += 8;
		num -= 8;
	}
	while (num--)
		*p++ = val;
	return (ptr);
}

int	frustum(t_triangle2 tri, t_fdf_data *data)
{
	int	score;
	int	width;
	int	height;
	int	min;

	min = 0 - FRUSTUM_CULLING_PRECISION;
	width = data->width + FRUSTUM_CULLING_PRECISION;
	height = data->height + FRUSTUM_CULLING_PRECISION;
	score = 0;
	score += (tri.a.x < min || tri.a.x >= width \
		|| tri.a.y < min || tri.a.y >= height);
	score += (tri.b.x < min || tri.b.x >= width \
		|| tri.b.y < min || tri.b.y >= height);
	score += (tri.c.x < min || tri.c.x >= width \
		|| tri.c.y < min || tri.c.y >= height);
	return (score > 2);
}

int	count_tri3(t_list *lst)
{
	t_vect3		*next_line;
	int			count;
	int			index;

	count = 0;
	while (lst)
	{
		index = -1;
		while (((t_vect3 *) lst->content)[++index].x != -1)
		{
			if (!lst->next || ((t_vect3 *) lst->content)[index + 1].x == -1)
				continue ;
			next_line = (t_vect3 *) lst->next->content;
			if (next_line[index].x == -1 || next_line[index + 1].x == -1)
				continue ;
			count++;
		}
		lst = lst->next;
	}
	return (count * 2);
}

/* int	is_point_segment(t_vect4 a, t_vect4 b, t_vect2 p)
{
	float	cross_product;

	cross_product = (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
	if (cross_product != 0)
		return (0);
	if ((p.x < a.x && p.x < b.x) || (p.x > a.x && p.x > b.x))
		return (0);
	if ((p.y < a.y && p.y < b.y) || (p.y > a.y && p.y > b.y))
		return (0);
	return (1);
}

int is_point_tricircum(t_vect2 p, t_triangle2 tri)
{
	int	score;

	score = 0;
	score += is_point_segment(tri.a, tri.b, p);
	score += is_point_segment(tri.b, tri.c, p);
	score += is_point_segment(tri.c, tri.a, p);
	return (score == 1);
} */