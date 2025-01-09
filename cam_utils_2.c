/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:58:46 by val               #+#    #+#             */
/*   Updated: 2025/01/09 23:44:56 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		cam_move_left(float speed, t_camera *cam)
{
	cam->pos = add(cam->pos, scale(cam->right, speed));
	return (1);
}

int		cam_move_forward(float speed, t_camera *cam)
{
	cam->pos = add(cam->pos, scale(cam->dir, speed));
	return (1);
}

int		cam_move_up(float speed, t_camera *cam)
{
	cam->pos = add(cam->pos, scale(cam->up, speed));
	return (1);
}

int		cam_rotate_up(float sensitivity, t_camera *cam)
{
	cam->euler.y += CAMERA_DEFAULT_SENSFACTOR * sensitivity;
	return (1);
}

int		cam_rotate_left(float sensitivity, t_camera *cam)
{
	cam->euler.x += CAMERA_DEFAULT_SENSFACTOR * sensitivity;
	return (1);
}
