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

float	interpolate(float a, float b, float t)
{
	return (a + t * (b - a));
}

float	normalize_angle(float angle)
{
	while (angle >= 360.0f)
		angle = 0.0f;
	while (angle < 0.0f)
		angle = 360.0f;
	return (angle);
}

int	is_point_in_cameradir(t_camera *cam, t_vect3 point, float fov)
{
	float fov_cos;
	float dot;
	t_vect3 to_point;

	fov_cos = cosf((fov * 0.5f) * (M_PI / 180.0f));
	to_point = subtract(point, cam->pos);
	dot = dot_product(cam->dir, to_point);
	return (dot * dot > fov_cos * fov_cos * dot_product(to_point, to_point));
}

float	fast_sqrt(float number)
{
    int32_t i;
    float	x2;
	float	y;

	if (number <= 0)
		return 0;
    x2 = number * 0.5f;
    y = number;
    i = *(int32_t *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (TREEHALFS - (x2 * y * y));
    return 1.0f / y;
}
