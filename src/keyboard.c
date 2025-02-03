/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/02/03 17:48:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_fdf_data *data)
{
	data->lastkey = keycode;
	return (1);
}

int	key_released(int keycode, t_fdf_data *data)
{
	if (keycode == XK_f)
	{
		data->mode += 1;
		if (data->mode >= MAX_DRAWING_MODE)
			data->mode = 0;
		cam_update(data->camera);
	}
	if (keycode == XK_equal)
	{
		data->color += 1;
	}
	if (keycode == XK_minus)
	{
		data->color -= 1;
	}
	data->lastkey = -1;
	return (1);
}

int	movement_keys(int keycode, t_fdf_data *data)
{
	t_camera		*camera;
	int				keypressed;

	camera = data->camera;
	camera->spd += CAMERA_DEFAULT_SPEED / 100;
	camera->spd = fmin(camera->spd, CAMERA_DEFAULT_SENSITIVITY * 4);
	keypressed = 0;
	if (keycode == XK_w)
		keypressed = cam_move_forward(camera->spd, camera);
	if (keycode == XK_s)
		keypressed = cam_move_forward(-camera->spd, camera);
	if (keycode == XK_a)
		keypressed = cam_move_left(-camera->spd, camera);
	if (keycode == XK_d)
		keypressed = cam_move_left(camera->spd, camera);
	if (keycode == XK_space)
		keypressed = cam_move_up(-camera->spd, camera);
	if (keycode == XK_Shift_L)
		keypressed = cam_move_up(camera->spd, camera);
	if (keypressed)
		cam_update(camera);
	return (keypressed);
}

int	camera_keys(int keycode, t_fdf_data *data)
{
	t_camera		*camera;
	int				keypressed;

	camera = data->camera;
	keypressed = 0;
	if (keycode == XK_Up)
		keypressed = cam_rotate(camera, -CAMERA_DEFAULT_SENSITIVITY, 0, 0);
	if (keycode == XK_Down)
		keypressed = cam_rotate(camera, CAMERA_DEFAULT_SENSITIVITY, 0, 0);
	if (keycode == XK_Right)
		keypressed = cam_rotate(camera, 0, -CAMERA_DEFAULT_SENSITIVITY, 0);
	if (keycode == XK_Left)
		keypressed = cam_rotate(camera, 0, CAMERA_DEFAULT_SENSITIVITY, 0);
	if (keypressed)
		cam_update(camera);
	return (1);
}

int	keys_parse(int keycode, t_fdf_data *data)
{
	close(data->file_fd);
	if (!try_open_file(&data->file_fd, data->file))
		return (0);
	if (!check_file(data->file_fd))
		return (0);
	if (!data->mesh || !data->points)
		return (0);
	free(data->mesh);
	ft_lstclear(&data->points, free);
	read_file(FILE_FACTOR * (keycode - XK_1 + 1), data);
	data->mesh = ft_calloc(count_tri3(data->points) + 1, sizeof(t_triangle3));
	if (!data->points || !data->mesh)
		return (printf("test"), 0);
	generate_mesh(data->mesh, data->points);
	return (1);
}
