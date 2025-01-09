/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:07:07 by val               #+#    #+#             */
/*   Updated: 2025/01/09 18:47:56 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start_managers(t_mlx_data *data)
{
	mlx_key_hook(data->window, key_manager, data);
	mlx_hook(data->window, DestroyNotify, 0, close_window, data);
	mlx_loop_hook(data->mlx, do_loop, data);
}

int	close_window(t_mlx_data *data)
{
	mlx_loop_end(data->mlx);
	ft_lstclear(&data->points, free);
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->title);
	ft_printf("\033[1;31mEXITING PROGRAM\033[0m\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_manager(int keycode, t_mlx_data	*data)
{
	ft_printf("\033[3;97mKEY RELEASED \033[0m%d\n", keycode);
	if (keycode == XK_Escape)
		return (close_window(data), 0);
	if (keycode == XK_space)
	{
		data->camera_dir.x = (rand() % 3) - 1;
		data->camera_dir.y = (rand() % 3) - 1;
		data->camera_dir.z = (rand() % 3) - 1;
		data->camera_moved = 1;
		return (0);
	}
	return (0);
}

int	do_loop(t_mlx_data *data)
{
	if (data->camera_moved)
	{
		data->camera_moved = 0;
		if (data->image)
			mlx_destroy_image(data->mlx, data->image);
		data->image = generate_wireframe(data);
		if (!data->image)
			return (EXIT_FAILURE);
		mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	}
	return (EXIT_SUCCESS);
}
