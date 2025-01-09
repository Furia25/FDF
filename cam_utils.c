/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:06:31 by val               #+#    #+#             */
/*   Updated: 2025/01/09 23:10:15 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera	*init_camera(void)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->pos = CAMERA_DEFAULT_POSITION;
	camera->euler = CAMERA_DEFAULT_EULERDIR;
	cam_update_rotation(camera);
	camera->up = normalize(CAMERA_DEFAULT_UP);
	camera->right = normalize(cross_product(camera->dir, camera->up));
	camera->spd = CAMERA_DEFAULT_SPEED;
	camera->sensivity = CAMERA_DEFAULT_SENSITIVITY;
	camera->moved = 0;
	return (camera);
}

void	cam_update_axis(t_camera *cam)
{
	cam->right = normalize(cross_product(cam->dir, CAMERA_DEFAULT_UP));
	cam->up = cross_product(cam->right, cam->dir);
}

void	cam_update_rotation(t_camera *cam)
{
	t_vect2	rad;
	t_vect2	yaw;
	t_vect2	pitch;
	t_vect3	result;

	rad.x = cam->euler.x * (M_PI / 180.0f);
	rad.y = cam->euler.y * (M_PI / 180.0f);
	yaw.x = cos(rad.x);
	yaw.y = sin(rad.x);
	pitch.x = cos(rad.y);
	pitch.y = sin(rad.y);
	result.x = cam->dir.x * yaw.x - cam->dir.z * yaw.y;
	result.y = cam->dir.y * pitch.x - cam->dir.z * pitch.y;
	result.z = cam->dir.x * yaw.y + cam->dir.z * yaw.x;
	cam->dir = normalize(result);
	cam_update_axis(cam);
	cam->moved = 1;
}
