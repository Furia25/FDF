/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:06:36 by val               #+#    #+#             */
/*   Updated: 2025/02/03 16:23:24 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline float	vec3_distance(t_vect3 a, t_vect3 b)
{
	return (fast_sqrt((a.x - b.x) * (a.x - b.x) + \
				(a.y - b.y) * (a.y - b.y) + \
				(a.z - b.z) * (a.z - b.z)));
}

inline float	vec3_length(t_vect3 v)
{
	return (fast_sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline t_vect3	normalize(t_vect3 v)
{
	float	length;

	length = vec3_length(v);
	if (length > 0)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}

inline t_vect3	vec3_rotate(t_quaternion q, t_vect3 v)
{
	t_quaternion	q_result;

	q = quaternion_normalize(q);
	q_result = quaternion_multiply(quaternion_multiply(q, \
		(t_quaternion){0, v.x, v.y, v.z}), quaternion_conjugate(q));
	return ((t_vect3){q_result.x, q_result.y, q_result.z});
}

inline t_vect4	vec3_to_homogeneous(t_vect3 v)
{
	return ((t_vect4){v.x, v.y, v.z, 1.0f});
}
