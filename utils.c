/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:17:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/08 17:18:33 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector2	make_vec2(int x, int y)
{
	t_vector2	result;
	
	result.x = x;
	result.y = y;
	return (result);
}

t_vector3	make_vec3(int x, int y, int z)
{
	t_vector3	result;
	
	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

