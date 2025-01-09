/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_managing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:26:44 by val               #+#    #+#             */
/*   Updated: 2025/01/10 00:32:49 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_draw_segment(t_vect3 a, t_vect3 b)
{
	int		steps;

	steps = 0;
	while (steps < SEGMENT_PRECISION)
	{
		img_draw_zdistpoint(0xABCDEF, project_point_cam(\
			get_interpolate_3d(a, b, t), \
			CAMERA_DEFAULT_FOCAL, data->camera, data), img);
		steps++;
	}
	index++;
}
