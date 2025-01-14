/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:13:14 by val               #+#    #+#             */
/*   Updated: 2025/01/14 19:23:24 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start_managers(t_fdf_data *data)
{
	mlx_set_font(data->mlx, data->window, \
		"-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1");
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, data->width / 2, data->height / 2);
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_hook(data->window, MotionNotify, \
		PointerMotionMask, mouse_manager, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_pressed, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, key_released, data);
	mlx_hook(data->window, DestroyNotify, 0, close_window, data);
	mlx_loop_hook(data->mlx, do_loop, data);
}

int	close_window(t_fdf_data *data)
{
	mlx_loop_end(data->mlx);
	ft_lstclear(&data->points, free);
	free(data->screen_buffer);
	free(data->z_buffer);
	free(data->mesh);
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data->camera);
	free(data->title);
	free(data);
	ft_printf("\033[1;31mEXITING PROGRAM\033[0m\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	mouse_manager(int x, int y, t_fdf_data *data)
{
	float	width;
	float	height;
	float	x_dif;
	float	y_dif;

	width = data->width * 0.5;
	height = data->height * 0.5;
	x_dif = (x - width) * 0.1;
	y_dif = (y - height) * 0.1;
	cam_rotate(data->camera, y_dif, -x_dif, 0);
	mlx_mouse_move(data->mlx, data->window, width, height);
	return (1);
}

void	mode_draw(t_fdf_data *data)
{
	memset_fast(data->screen_buffer, 0, \
		data->width * data->height * sizeof(t_argb));
	memset_fast(data->z_buffer, \
		1024, data->width * data->height * sizeof(float));
	if (data->mode == POINT_MODE)
		rasterize_wireframe(data->points, data);
	else if (data->mode == POLYGON_MODE)
		rasterize_tri(data);
	else if (data->mode == WIREFRAME_MODE)
		rasterize_points(data->points, data);
}

int	do_loop(t_fdf_data *data)
{
	char	*temp;

	key_manager(data->lastkey, data);
	if (data->camera->moved)
	{
		data->camera->moved = 0;
		if (data->image)
			mlx_destroy_image(data->mlx, data->image);
		generate_screen(data);
		if (!data->image)
			return (close_window(data));
		mode_draw(data);
		img_draw_screen(&data->image_data, data);
		mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
		mlx_string_put(data->mlx, data->window, 10, 10, 0xFFFFFF, data->title);
		temp = ft_strjoin("Mode : ", ft_itoa(data->mode));
		if (temp)
			mlx_string_put(data->mlx, data->window, 10, 30, 0xFFFFFF, temp);
		free(temp);
		temp = ft_strjoin("Color : ", ft_itoa(data->color));
		if (temp)
			mlx_string_put(data->mlx, data->window, 10, 50, 0xFFFFFF, temp);
		free(temp);
	}
	return (EXIT_SUCCESS);
}
