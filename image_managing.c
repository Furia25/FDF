/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:33:25 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/11 18:24:52 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	img_set_pixel(t_argb rgb, t_vect2 co, t_image_data *img)
{
	int	pixel;
	int	color;

	if (co.x < 0 || co.x > img->width || co.y < 0 || co.y > img->height)
		return ;
	pixel = ((int) co.y * img->size_line) + ((int) co.x * 4);
	color = argb_to_int(rgb);
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

void	img_set_rect(t_argb color, t_vect2 co, t_vect2 size, t_image_data *img)
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

void	img_draw_disk(t_argb color, t_vect2 cord, int radius, t_image_data *img)
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

void	img_draw_circle(t_argb color, t_vect2 coord, int radius, t_image_data *img)
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

void	img_draw_point(t_argb color, t_vect4 point, float z, t_image_data *img)
{
	float	point_size;

	if (point.z <= 0 || point.x <= 0 ||  point.y <= 0)
		return ;
	point_size = PERSPECTIVE_FACTOR * (1 /point.w);
	color = hsv_to_argb((t_hsv){(int) (z * 10) % 360, 255, 255});
	img_draw_disk(color, (t_vect2){point.x, point.y}, point_size, img);
}
