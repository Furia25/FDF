/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:04:33 by val               #+#    #+#             */
/*   Updated: 2025/02/03 16:19:20 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline t_vect3	add(t_vect3 a, t_vect3 b)
{
	return ((t_vect3){a.x + b.x, a.y + b.y, a.z + b.z});
}

inline t_vect3	subtract(t_vect3 a, t_vect3 b)
{
	return ((t_vect3){a.x - b.x, a.y - b.y, a.z - b.z});
}

inline t_vect3	scale(t_vect3 v, float scalar)
{
	return ((t_vect3){v.x * scalar, v.y * scalar, v.z * scalar});
}

inline t_vect3	cross_product(t_vect3 a, t_vect3 b)
{
	return ((t_vect3)
		{
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		});
}

inline float	dot_product(t_vect3 a, t_vect3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
