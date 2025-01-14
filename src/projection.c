/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:21:39 by val               #+#    #+#             */
/*   Updated: 2025/01/14 03:48:30 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix4	multiply_matrix4(t_matrix4 mat1, t_matrix4 mat2)
{
	t_matrix4	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = 0.0f;
			k = 0;
			while (k < 4)
			{
				result.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix4	get_perspective_matrix(float f, float aspect, float near, float far)
{
	t_matrix4	mat;
	float		tan_half_fov;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	tan_half_fov = tanf(f * 0.5f);
	mat.m[0][0] = 1.0f / (aspect * tan_half_fov);
	mat.m[1][1] = 1.0f / tan_half_fov;
	mat.m[2][2] = -((far + near) / (far - near));
	mat.m[2][3] = (2.0f * far * near) / (near - far);
	mat.m[3][2] = -1.0f;
	return (mat);
}

t_matrix4	get_view_matrix(t_vect3 cam_pos, t_vect3 dir, t_vect3 right)
{
	t_matrix4	mat;
	t_vect3		up_normalized;

	up_normalized = cross_product(right, dir);
	up_normalized = normalize(up_normalized);
	mat.m[0][0] = right.x;
	mat.m[0][1] = right.y;
	mat.m[0][2] = right.z;
	mat.m[0][3] = -dot_product(right, cam_pos);
	mat.m[1][0] = up_normalized.x;
	mat.m[1][1] = up_normalized.y;
	mat.m[1][2] = up_normalized.z;
	mat.m[1][3] = -dot_product(up_normalized, cam_pos);
	mat.m[2][0] = -dir.x;
	mat.m[2][1] = -dir.y;
	mat.m[2][2] = -dir.z;
	mat.m[2][3] = dot_product(dir, cam_pos);
	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 0.0f;
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_vect4	vec4_multiply_matrix4(t_matrix4 mat, t_vect4 v)
{
	t_vect4	result;

	result.x = mat.m[0][0] * v.x + mat.m[0][1] * v.y \
		+ mat.m[0][2] * v.z + mat.m[0][3] * v.w;
	result.y = mat.m[1][0] * v.x + mat.m[1][1] * v.y \
		+ mat.m[1][2] * v.z + mat.m[1][3] * v.w;
	result.z = mat.m[2][0] * v.x + mat.m[2][1] * v.y \
		+ mat.m[2][2] * v.z + mat.m[2][3] * v.w;
	result.w = mat.m[3][0] * v.x + mat.m[3][1] * v.y \
		+ mat.m[3][2] * v.z + mat.m[3][3] * v.w;
	return (result);
}

t_vect4	project_point_cam(t_vect3 p, t_camera *cam)
{
	t_vect4	point;
	t_vect4	projected;

	point = vec3_to_homogeneous(p);
	projected = vec4_multiply_matrix4(cam->m_final, point);
	if (projected.w != 0.0f)
	{
		projected.x /= projected.w;
		projected.y /= projected.w;
		projected.z /= projected.w;
	}
	if (projected.w < 0)
		return ((t_vect4){-1, -1, -1, -1});
	projected.x = (int)((-projected.x + 1.0f) * cam->width * 0.5);
	projected.y = (int)((-projected.y + 1.0f) * cam->height * 0.5);
	return (projected);
}
