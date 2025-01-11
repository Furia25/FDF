/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   managers.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: val <val@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/01/09 14:07:07 by val   #+##+# */
/*   Updated: 2025/01/09 19:59:45 by val  ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "fdf.h"

void	start_managers(t_fdf_data *data)
{
	mlx_key_hook(data->window, key_manager, data);
	mlx_hook(data->window, DestroyNotify, 0, close_window, data);
	mlx_loop_hook(data->mlx, do_loop, data);
}

int	close_window(t_fdf_data *data)
{
	mlx_loop_end(data->mlx);
	ft_lstclear(&data->points, free);
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx){
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

int	movement_manager(int keycode, t_fdf_data *data)
{
	t_camera		*camera;
	int				keypressed;

	camera = data->camera;
	keypressed = 0;
	if (keycode == XK_z)
		keypressed = cam_move_forward(camera->spd, camera);
	if (keycode == XK_s)
		keypressed = cam_move_forward(-camera->spd, camera);
	if (keycode == XK_q)
		keypressed = cam_move_left(-camera->spd, camera);
	if (keycode == XK_d)
		keypressed = cam_move_left(camera->spd, camera);
	if (keycode == XK_space)
		keypressed = cam_move_up(-camera->spd, camera);
	if (keycode == XK_Shift_L)
		keypressed = cam_move_up(camera->spd, camera);
	if (keycode == XK_Up)
		keypressed = cam_rotate(camera, -CAMERA_DEFAULT_SENSITIVITY, 0);
	if (keycode == XK_Down)
		keypressed = cam_rotate(camera, CAMERA_DEFAULT_SENSITIVITY, 0);
	if (keycode == XK_Right)
		keypressed = cam_rotate(camera, 0, -CAMERA_DEFAULT_SENSITIVITY);
	if (keycode == XK_Left)
		keypressed = cam_rotate(camera, 0, CAMERA_DEFAULT_SENSITIVITY);
	if (keypressed)
		cam_update(camera);
	return (1);
}

int	key_manager(int keycode, t_fdf_data	*data)
{
	ft_printf("\033[3;97mKEY RELEASED \033[0m%d\n", keycode);
	if (keycode == XK_Escape)
		return (close_window(data), 0);
	return (movement_manager(keycode, data));
}

int	do_loop(t_fdf_data *data)
{
	if (data->camera->moved)
	{
		data->camera->moved = 0;
		if (data->image)
			mlx_destroy_image(data->mlx, data->image);
		data->image = generate_wireframe(data);
		if (!data->image)
			return (EXIT_FAILURE);
		mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	}
	return (EXIT_SUCCESS);
}
