/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_managing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:26:44 by val               #+#    #+#             */
/*   Updated: 2025/01/14 19:13:51 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	img_set_bsegment(t_argb color, t_vect3 a, t_vect3 b, t_fdf_data *data)
{
	int		steps;
	int		index;
	float	dist;
	t_vect3	diff;
	t_vect3	interpolated;

	dist = vec3_distance(a, data->camera->pos);
	diff = subtract(b, a);
	steps = (int)(SEGMENT_PRECISION * fmaxf(0.4f, vec3_length(diff) / 25.0f) \
		* fmaxf(0.05f, expf(-dist / 40.0f)));
	if (steps < 1)
		steps = 1;
	index = 0;
	while (index < steps)
	{
		interpolated = add(a, scale(diff, (float)index / (steps - 1)));
		img_set_point(color, \
			project_point_cam(interpolated, data->camera), \
			interpolated.y, \
			data);
		index++;
	}
}

void	img_set_disk(t_argb color, t_vect2 cord, int radius, t_fdf_data *data)
{
	int	dx;
	int	dy;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				img_set_pixel(color, cord.x + dx, cord.y + dy, data);
			dx++;
		}
		dy++;
	}
}

void	img_set_circle(t_argb color, t_vect2 co, int radius, t_fdf_data *data)
{
	float		angle;
	int			index;

	index = 0;
	while (index < CIRCLE_PRECISION)
	{
		angle = 2 * M_PI * index / CIRCLE_PRECISION;
		img_set_pixel(color, co.x + radius * cos(angle), \
			co.y + radius * sin(angle), data);
		index++;
	}
}

void	img_set_point(t_argb color, t_vect4 point, float z, t_fdf_data *data)
{
	float	point_size;

	if (point.z <= 0.1 || point.x <= 0 || point.y <= 0)
		return ;
	point_size = PERSPECTIVE_FACTOR * (1 / point.w);
	color = hsv_to_argb((t_hsv){(int)(-z * 20 + data->color) % 360, 1, 1});
	img_set_disk(color, (t_vect2){point.x, point.y}, point_size, data);
}
