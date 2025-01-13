/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:33:25 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/12 18:54:10 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	img_draw_pixel(t_argb argb, int x, int y, t_image_data *img)
{
	int	pixel;
	int	color;
	
	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return ;
	pixel = ((int) y * img->size_line) + ((int) x * 4);
	color = argb_to_int(argb);
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

void	img_draw_screen(t_image_data *img, t_fdf_data *data)
{
	t_argb	*screen;
	t_argb	temp;
	int		x;
	int		y;

	screen = data->screen_buffer;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			temp = screen[y * data->width + x];
			if (!(temp.r == 0 && temp.g == 0 && temp.a == 0))
				img_draw_pixel(temp, x, y, img);
			x++;
		}
		y++;
	}
}

void	img_set_pixel(t_argb color, int x, int y, t_fdf_data *data)
{
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	data->screen_buffer[y * data->width + x] = color;
}

void	img_set_pixel_zbuffer(t_argb color, t_vect4 point, t_fdf_data *data)
{
	if (point.x < 0 || point.x >= data->width || point.y < 0 || point.y >= data->height)
		return ;
	if (point.w < data->z_buffer[(int)(point.y * data->width + point.x)])
		return ;
	data->screen_buffer[(int)(point.y * data->width + point.x)] = color;
	data->z_buffer[(int)(point.y * data->width + point.x)] = point.w;
}

void	img_set_rect(t_argb color, t_vect2 co, t_vect2 size, t_fdf_data *data)
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
			img_set_pixel(color, co.x + i, co.y + y, data);
			y++;
		}
		i++;
	}
}
