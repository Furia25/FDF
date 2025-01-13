/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:06:43 by val               #+#    #+#             */
/*   Updated: 2025/01/13 19:20:47 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	cam_rotate(t_camera *camera, float yaw, float pitch, float roll)
{
	t_quaternion	pitch_q;
	t_quaternion	yaw_q;
	t_quaternion	roll_q;
	t_quaternion	combined_q;
	
	pitch_q = quaternion_from_axis_angle(camera->up, pitch);
	yaw_q = quaternion_from_axis_angle(camera->right, yaw);
	combined_q = quaternion_multiply(yaw_q, pitch_q);
	roll_q = quaternion_from_axis_angle(camera->dir, roll);
	combined_q = quaternion_multiply(combined_q, roll_q);
	camera->dir = vec3_rotate(combined_q, camera->dir);
	camera->dir = normalize(camera->dir);
	camera->right = cross_product(camera->dir, (t_vect3){0, 1, 0});
    camera->right = normalize(camera->right);
	camera->up = cross_product(camera->right, camera->dir);
    camera->up = normalize(camera->up);
	cam_update(camera);
	return (1);
}

t_camera	*init_camera(float wwindow, float hwindow)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->pos = (t_vect3){
		CAMERA_DEFAULT_X,
		CAMERA_DEFAULT_Y,
		CAMERA_DEFAULT_Z
	};
	camera->dir = (t_vect3){0, 0, -1};
	camera->width = wwindow;
	camera->height = hwindow;
	camera->right = cross_product(camera->dir, (t_vect3){0, 1, 0});
	camera->right = normalize(camera->right);
	camera->up = cross_product(camera->right, camera->dir);
    camera->up = normalize(camera->up);
	camera->fov = CAMERA_DEFAULT_FOCAL;
	camera->m_perspective = get_perspective_matrix(camera->fov, wwindow / hwindow, 0.1f, 100.0f);
	cam_update(camera);
	camera->spd = CAMERA_DEFAULT_SPEED;
	camera->sensivity = CAMERA_DEFAULT_SENSITIVITY;
	camera->moved = 0;
	return (camera);
}

void	cam_update(t_camera *cam)
{
	cam->m_view = get_view_matrix(cam->pos, cam->dir, cam->right);
	cam->m_final = multiply_matrix4(cam->m_perspective, cam->m_view);
	cam->moved = 1;
}
