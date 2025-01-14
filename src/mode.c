/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:15:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/14 03:32:22 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_points(t_list *lst, t_fdf_data *data)
{
	int		index;
	t_vect3	*array;
	t_argb	color;

	while (lst)
	{
		array = (t_vect3 *) lst->content;
		index = -1;
		while (array[++index].x != -1)
		{
			if (!is_point_in_cameradir(
					data->camera, array[index], data->camera->fov))
				continue ;
			color = (t_argb){0, 0, 0, 0};
			if (array[index + 1].x != -1)
				img_set_bsegment(color, array[index], array[index + 1], data);
			if (lst->next)
				img_set_bsegment(color, array[index], \
				((t_vect3 *)lst->next->content)[index], data);
		}
		lst = lst->next;
	}
}

void	triangle_test(t_fdf_data *data)
{
	t_triangle3	*mesh;
	t_triangle2	temp;
	float		a;
	size_t		i;

	i = 0;
	mesh = data->mesh;
	while (mesh[i].a.x != -1)
	{
		temp = (t_triangle2){
			project_point_cam(mesh[i].a, data->camera),
			project_point_cam(mesh[i].b, data->camera),
			project_point_cam(mesh[i].c, data->camera),
		};
		a = -mesh[i].a.y + -mesh[i].b.y + -mesh[i].c.y / 3;
		img_rasterize_triangle(
			temp, (t_argb){0, a * 10 + 200, a * 15 - 255, 255}, data);
		i++;
	}
}
