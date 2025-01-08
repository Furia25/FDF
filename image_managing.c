/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:33:25 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/08 17:17:51 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_set_pixel(int color, t_vector2 coord, t_image_data *img)
{
	int	pixel;

	pixel = GET_PIXEL(coord.x, coord.y, img->size_line);
	if(img->pbits != 32)
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

void	img_set_rectangle(int color, t_vector2 coord, t_vector2 size, t_image_data *img)
{
	unsigned int	i;
	unsigned int 	y;

	i = 0;
	y = 0;
	while (i < (unsigned int) size.x)
	{
		y = 0;
		while (y < (unsigned int) size.y)
		{
			img_set_pixel(color,make_vec2(coord.x + i, coord.y + y), img);
			y++;
		}
		i++;
	}
}
