/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   math_utils.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: val <val@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/01/08 17:17:45 by vdurand   #+##+# */
/*   Updated: 2025/01/09 18:10:13 by val  ###   ########.fr   */
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

t_vect3	project_point_cam(t_vect3 point, float focalLength, t_mlx_data *data)
{
	t_vect3		projected_point;
	t_vect3		vector_to_point;
	float		distance;

	vector_to_point.x = point.x - data->camera.x;
	vector_to_point.y = point.y - data->camera.y;
	vector_to_point.z = point.z - data->camera.z;
	distance = dot_product(vector_to_point, data->camera_dir);
	projected_point.x = (point.x * focalLength) / distance;
	projected_point.y = (point.y * focalLength) / distance;
	projected_point.x = (projected_point.x + 1) * data->width / 2;
	projected_point.y = (projected_point.y + 1) * data->height / 2;
	projected_point.z = distance;
	return (projected_point);
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
