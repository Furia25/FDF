/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   rasterization.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: val <val@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/01/13 01:58:59 by val   #+##+# */
/*   Updated: 2025/01/13 02:37:33 by val  ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "fdf.h"

void	sort_vertices_by_y(t_vect4 *a, t_vect4 *b, t_vect4 *c)
{
	t_vect4	temp;

	if (a->y > b->y)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
	if (b->y > c->y)
	{
		temp = *b;
		*b = *c;
		*c = temp;
	}
	if (a->y > b->y)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

t_bbox	get_bounding_box(t_triangle2 triangle)
{
	t_bbox	box;

	box.x_min = (int)fminf(fminf(triangle.a.x, triangle.b.x), triangle.c.x);
	box.x_max = (int)fmaxf(fmaxf(triangle.a.x, triangle.b.x), triangle.c.x);
	box.y_min = (int)fminf(fminf(triangle.a.y, triangle.b.y), triangle.c.y);
	box.y_max = (int)fmaxf(fmaxf(triangle.a.y, triangle.b.y), triangle.c.y);
	return (box);
}

int	is_point_in_triangle(float x, float y, t_triangle2 triangle)
{
	float	alpha;
	float	beta;
	float	gamma;

	alpha = ((triangle.b.y - triangle.c.y) * (x - triangle.c.x) + \
			(triangle.c.x - triangle.b.x) * (y - triangle.c.y)) /\
			((triangle.b.y - triangle.c.y) * (triangle.a.x - triangle.c.x) \
			+ (triangle.c.x - triangle.b.x) * \
			(triangle.a.y - triangle.c.y));
	beta = ((triangle.c.y - triangle.a.y) * (x - triangle.c.x) + \
			(triangle.a.x - triangle.c.x) * (y - triangle.c.y)) / \
			((triangle.b.y - triangle.c.y) * (triangle.a.x - triangle.c.x) \
			+ (triangle.c.x - triangle.b.x) * \
			(triangle.a.y - triangle.c.y));
	gamma = 1.0f - alpha - beta;
	return (alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f);
}

t_vect2	interpolate_zw(float x, float y, t_triangle2 triangle)
{
	t_vect2	result;
	float	alpha;
	float	beta;
	float	gamma;

	alpha = ((triangle.b.y - triangle.c.y) * (x - triangle.c.x) + \
			(triangle.c.x - triangle.b.x) * (y - triangle.c.y)) / \
			((triangle.b.y - triangle.c.y) * \
			(triangle.a.x - triangle.c.x) + \
			(triangle.c.x - triangle.b.x) * (triangle.a.y - triangle.c.y));
	beta = ((triangle.c.y - triangle.a.y) * (x - triangle.c.x) + \
			(triangle.a.x - triangle.c.x) * (y - triangle.c.y)) / \
			((triangle.b.y - triangle.c.y) * \
			(triangle.a.x - triangle.c.x) + \
			(triangle.c.x - triangle.b.x) * (triangle.a.y - triangle.c.y));
	gamma = 1.0f - alpha - beta;
	result.x = (alpha * triangle.a.z + beta * \
		triangle.b.z + gamma * triangle.c.z);
	result.y = (alpha * triangle.a.w + beta * \
		triangle.b.w + gamma * triangle.c.w);
	return (result);
}

void	img_rasterize_triangle(t_triangle2 tri, t_argb c, t_fdf_data *data)
{
	t_vect2	zw;
	int		y;
	int		x;
	t_bbox	box;

	if (tri.a.w <= -1 || tri.b.w <= -1 || tri.b.w <= -1)
		return ;
	sort_vertices_by_y(&tri.a, &tri.b, &tri.c);
	box = get_bounding_box(tri);
	y = box.y_min;
	while (y <= box.y_max)
	{
		x = box.x_min;
		while (x <= box.x_max)
		{
			if (is_point_in_triangle(x, y, tri))
			{
				zw = interpolate_zw(x, y, tri);
				img_set_pixel_zbuffer(c, (t_vect4){x, y, zw.x, zw.y}, data);
			}
			x++;
		}
		y++;
	}
}
