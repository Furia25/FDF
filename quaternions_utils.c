/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:39:40 by val               #+#    #+#             */
/*   Updated: 2025/01/11 16:02:57 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_quaternion    quaternion_normalize(t_quaternion q)
{
    float   length;
    float   inv_length;
    
    length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    if (length > 0.0f) {
        inv_length = 1.0f / length;
        q.w *= inv_length;
        q.x *= inv_length;
        q.y *= inv_length;
        q.z *= inv_length;
    }
    return (q);
}

t_quaternion	quaternion_multiply(t_quaternion q1, t_quaternion q2)
{
	t_quaternion result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z;
	result.z = q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x;
    return (result);
}

t_quaternion	quaternion_conjugate(t_quaternion q)
{
	return ((t_quaternion){q.w, -q.x, -q.y, -q.z});
}

t_quaternion	quaternion_from_axis_angle(t_vect3 axis, float angle)
{
	float   s;
    float   half_angle;

    half_angle = (angle * M_PI / 180.0f) / 2.0f;
	s = sin(half_angle);
	return (quaternion_normalize((t_quaternion)
	{
        cos(half_angle),
        axis.x * s,
        axis.y * s,
        axis.z * s
	}));
}
