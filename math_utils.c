/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   math_utils.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: val <val@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/01/09 20:27:01 by val   #+##+# */
/*   Updated: 2025/01/09 21:48:06 by val  ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_vect3	get_interpolate_3d(t_vect3 p1, t_vect3 p2, float t)
{
	t_vect3	result;

	result.x = (1 - t) * p1.x + t * p2.x;
	result.y = (1 - t) * p1.y + t * p2.y;
	result.z = (1 - t) * p1.z + t * p2.z;
	return (result);
}

t_vect3	project_point_cam(t_vect3 p, float f, t_camera *cam, t_fdf_data *data)
{
	t_vect3	p_camera;
	t_vect3	p_oncam;
	t_vect3	projected;
	float 	fov_scale;

	p_camera = subtract(p, cam->pos);
	p_oncam.x = dot_product(p_camera, cam->right);
	p_oncam.y = dot_product(p_camera, cam->up);
	p_oncam.z = dot_product(p_camera, cam->dir);
	if (p_oncam.z <= 0.01f)
		return ((t_vect3){-1, -1, -1});
	fov_scale = 1.0f / tan(f / 2.0f);
	projected.x = (p_oncam.x / p_oncam.z) * fov_scale * \
		data->width / data->height * (data->width / 2) + (data->width / 2);
	projected.y = (p_oncam.y / p_oncam.z) * fov_scale * (data->height / 2) \
		+ (data->height / 2);
	return (projected);
}

t_vect3	normalize(t_vect3 v)
{
	float	length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length > 0)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}
