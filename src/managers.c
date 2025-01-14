/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:13:14 by val               #+#    #+#             */
/*   Updated: 2025/01/14 03:40:27 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start_managers(t_fdf_data *data)
{
	mlx_do_key_autorepeatoff(data->mlx);
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

int	do_loop(t_fdf_data *data)
{
	key_manager(data->lastkey, data);
	if (data->camera->moved)
	{
		data->camera->moved = 0;
		if (data->image)
			mlx_destroy_image(data->mlx, data->image);
		generate_screen(data);
		if (!data->image)
			return (close_window(data));
		memset_fast(data->screen_buffer, 0, \
			data->width * data->height * sizeof(t_argb));
		memset_fast(data->z_buffer, \
			5000, data->width * data->height * sizeof(float));
		if (data->mode == -1)
			set_points(data->points, data);
		else
			triangle_test(data);
		img_draw_screen(&data->image_data, data);
		mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	}
	return (EXIT_SUCCESS);
}
