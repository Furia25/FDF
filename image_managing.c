/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:33:25 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/10 00:17:16 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	img_set_pixel(int color, t_vect2 coord, t_image_data *img)
{
	int	pixel;

	if (coord.x < 0 || coord.x > img->width)
		return ;
	if (coord.y < 0 || coord.y > img->height)
		return ;
	pixel = ((int) coord.y * img->size_line) + ((int) coord.x * 4);
	if (img->pbits != 32)
		color = mlx_get_color_value(img->connection, color);
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = (color >> 24);
		img->buffer[pixel + 1] = (color >> 16) & 0xFF;
		img->buffer[pixel + 2] = (color >> 8) & 0xFF;
		img->buffer[pixel + 3] = (color) & 0xFF;
	}
	else
	{
		img->buffer[pixel + 0] = (color) & 0xFF;
		img->buffer[pixel + 1] = (color >> 8) & 0xFF;
		img->buffer[pixel + 2] = (color >> 16) & 0xFF;
		img->buffer[pixel + 3] = (color >> 24);
	}
}

void	img_set_rect(int color, t_vect2 co, t_vect2 size, t_image_data *img)
{
	unsigned int	i;
	unsigned int	y;

	i = 0;
	y = 0;
	while (i < (unsigned int) size.x)
	{
		y = 0;
		while (y < (unsigned int) size.y)
		{
			img_set_pixel(color, (t_vect2){co.x + i, co.y + y}, img);
			y++;
		}
		i++;
	}
}

void	img_draw_disk(int color, t_vect2 cord, int radius, t_image_data *img)
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
				img_set_pixel(color, (t_vect2){cord.x + dx, cord.y + dy}, img);
			dx++;
		}
		dy++;
	}
}

void	img_draw_circle(int color, t_vect2 coord, int radius, t_image_data *img)
{
	float		angle;
	t_vect2		xy;
	int			index;

	index = 0;
	while (index < CIRCLE_PRECISION)
	{
		angle = 2 * M_PI * index / CIRCLE_PRECISION;
		xy.x = coord.x + radius * cos(angle);
		xy.y = coord.y + radius * sin(angle);
		img_set_pixel(color, xy, img);
		index++;
	}
}

void	img_draw_zdistpoint(int color, t_vect3 point, t_image_data *img)
{
	float	point_size;

	if (point.z <= 0 || point.x <= 0 ||  point.y <= 0)
		return ;
	point_size = PERSPECTIVE_FACTOR / point.z;
	img_draw_disk(color, (t_vect2){point.x, point.y}, point_size, img);
}
