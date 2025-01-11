/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_managing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:26:44 by val               #+#    #+#             */
/*   Updated: 2025/01/11 16:47:47 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_draw_segment(t_argb color, t_vect3 a, t_vect3 b, t_image_data *img)
{
	int		steps;
	int		index;
	float	dist;
	t_vect3 diff;
	t_vect3 interpolated;

	dist = vec3_distance(a, img->data->camera->pos);
	diff = subtract(b, a);
	steps = (int)(SEGMENT_PRECISION * fmaxf(0.2f, vec3_length(diff) / 40.0f) * fmaxf(0.3f, expf(-dist / 80.0f)));
	if (steps < 1)
		steps = 1;
	index = 0;
	while (index < steps)
	{
		interpolated = add(a, scale(diff, (float)index / (steps - 1)));
		img_draw_point(color, \
			project_point_cam(interpolated, img->data->camera), \
			interpolated.z, \
			img);
		index++;
	}
}
