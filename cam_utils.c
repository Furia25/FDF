/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   cam_utils.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: val <val@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/01/09 22:06:31 by val   #+##+# */
/*   Updated: 2025/01/10 00:03:10 by val  ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "fdf.h"

void	cam_update_axis(t_camera *cam)
{
	cam->right = normalize(cross_product(cam->dir, CAMERA_DEFAULT_UP));
	cam->up = cross_product(cam->right, cam->dir);
}

t_camera	*init_camera(void)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->pos = CAMERA_DEFAULT_POSITION;
	camera->dir = CAMERA_DEFAULT_DIR;
	camera->euler = CAMERA_DEFAULT_EULERDIR;
	cam_update_axis(camera);
	cam_update(camera);
	camera->spd = CAMERA_DEFAULT_SPEED;
	camera->sensivity = CAMERA_DEFAULT_SENSITIVITY;
	camera->moved = 0;
	return (camera);
}

void	cam_update(t_camera *cam)
{
	t_vect2 rad;
	t_vect2 yaw;
	t_vect2 pitch;
	t_vect3 result;

	cam->euler.x = normalize_angle(cam->euler.x);
	cam->euler.y = normalize_angle(cam->euler.y);
	rad.x = cam->euler.x * (M_PI / 180.0f);
	rad.y = cam->euler.y * (M_PI / 180.0f);
	yaw.x = cos(rad.x);
	yaw.y = sin(rad.x);
	pitch.x = cos(rad.y);
	pitch.y = sin(rad.y);
	result.x = yaw.x * pitch.x;
	result.y = pitch.y;
	result.z = yaw.y * pitch.x;
	cam->dir = normalize(result);
	cam_update_axis(cam);
	cam->moved = 1;
}
