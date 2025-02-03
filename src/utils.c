/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:44:13 by val               #+#    #+#             */
/*   Updated: 2025/02/03 17:49:29 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>

int	close_window(t_fdf_data *data)
{
	if (data->file_fd != -1)
		close(data->file_fd);
	mlx_loop_end(data->mlx);
	ft_lstclear(&data->points, free);
	free(data->screen_buffer);
	free(data->z_buffer);
	if (data->mesh)
		free(data->mesh);
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data->camera);
	free(data->title);
	free(data);
	ft_printf("\033[1;31mEXITING PROGRAM\033[0m\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	*memset_fast(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	val;
	uint64_t		val64;

	val = (unsigned char)value;
	p = ptr;
	while (((uintptr_t)p & 7) && num--)
		*p++ = val;
	val64 = (uint64_t)val | ((uint64_t)val << 8) | ((uint64_t)val << 16) \
	| ((uint64_t)val << 24) | ((uint64_t)val << 48) | ((uint64_t)val << 56);
	while (num >= 8)
	{
		*(uint64_t *)p = val64;
		p += 8;
		num -= 8;
	}
	while (num--)
		*p++ = val;
	return (ptr);
}

int	frustum(t_triangle2 tri, t_fdf_data *data)
{
	int	score;
	int	width;
	int	height;
	int	min;

	min = 0 - FRUSTUM_CULLING_PRECISION;
	width = data->width + FRUSTUM_CULLING_PRECISION;
	height = data->height + FRUSTUM_CULLING_PRECISION;
	score = 0;
	score += (tri.a.x < min || tri.a.x >= width \
		|| tri.a.y < min || tri.a.y >= height);
	score += (tri.b.x < min || tri.b.x >= width \
		|| tri.b.y < min || tri.b.y >= height);
	score += (tri.c.x < min || tri.c.x >= width \
		|| tri.c.y < min || tri.c.y >= height);
	return (score > 2);
}

int	count_tri3(t_list *lst)
{
	t_vect3		*next_line;
	int			count;
	int			index;

	count = 0;
	while (lst)
	{
		index = -1;
		while (((t_vect3 *) lst->content)[++index].x != -1)
		{
			if (!lst->next || ((t_vect3 *) lst->content)[index + 1].x == -1)
				continue ;
			next_line = (t_vect3 *) lst->next->content;
			if (next_line[index].x == -1 || next_line[index + 1].x == -1)
				continue ;
			count++;
		}
		lst = lst->next;
	}
	return (count * 2);
}
