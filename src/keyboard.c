/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/13 19:36:12 by vdurand          ###   ########.fr       */
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
		data->mode *= -1;
		cam_update(data->camera);
	}
	data->lastkey = -1;
	return (1);
}

int	key_manager(int lastkey, t_fdf_data *data)
{
	if (lastkey == XK_Escape)
		return (close_window(data), 1);
	if (lastkey != -1)
	{
		if (!movement_keys(lastkey, data))
			data->camera->spd = CAMERA_DEFAULT_SPEED;
		camera_keys(lastkey, data);
	}
	return (1);
}

int	movement_keys(int keycode, t_fdf_data *data)
{
	t_camera		*camera;
	int				keypressed;

	camera = data->camera;
	camera->spd += CAMERA_DEFAULT_SPEED / 100;
	camera->spd = fmin(camera->spd, CAMERA_DEFAULT_SENSITIVITY * 2);
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
