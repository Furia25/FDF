/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:47:15 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/13 19:15:43 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/* void	test(void *param)
{
	int	index;
	t_vect3	*lst;

	lst = (t_vect3 *) param;
	index = 0;
	while (lst[index].x != -1)
	{
		printf("| X : %.2f, Y : %.2f, Z : %.2f | ", lst[index].x, lst[index].y, lst[index].z);
		index++;
	}
	printf("\n");
} */

int	count_triangles(t_list *lst)
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

void create_subtri(t_triangle3 *mesh, size_t *tri, t_vect3 *vec, t_vect3 *next)
{
	t_vect3	top_left;
	t_vect3	top_right;
	t_vect3	bot_left;
	t_vect3	bot_right;

	top_left = *vec;
	top_right = *(vec + 1);
	bot_left = *next;
	bot_right = *(next + 1);
	mesh[*tri] = (t_triangle3){top_left, top_right, bot_left};
	*tri += 1;
	mesh[*tri] = (t_triangle3){top_right, bot_right, bot_left};
	*tri += 1;
	return ;
}

t_triangle3	*generate_mesh(t_triangle3 *mesh, t_list *lst)
{
	t_vect3		*vec;
	t_vect3		*next;
	int			i;
	size_t		tri;

	if (!mesh)
		return (NULL);
	tri = 0;
	while (lst)
	{
		i = -1;
		vec = ((t_vect3 *) lst->content);
		while (vec[++i].x != -1)
		{
			if (!lst->next || vec[i + 1].x == -1)
				continue ;
			next = (t_vect3 *) lst->next->content;
			if (next[i].x == -1 || next[i + 1].x == -1)
				continue ;
			create_subtri(mesh, &tri, vec + i, next + i);
		}
		lst = lst->next;
	}
	mesh[tri] = (t_triangle3){(t_vect3){-1, -1, -1}, \
		(t_vect3){-1, -1, -1}, (t_vect3){-1, -1, -1}};
	return (mesh);
}

void	*generate_screen(t_fdf_data *data)
{
	t_image_data	img;

	img.height = data->height;
	img.width = data->width;
	img.connection = data->mlx;
	data->image = mlx_new_image(data->mlx, img.height, img.width);
	if (!data->image)
		return (NULL);
	img.buffer = mlx_get_data_addr(data->image, &img.pbits,
			&img.size_line, &img.endian);
	if (!img.buffer)
		return (NULL);
	data->image_data = img;
	return (data->image);
}

int	init_data(t_fdf_data *data, int fd, char *title)
{
	data->width = WINDOW_WIDTH;
	data->height = WINDOW_HEIGHT;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free(data), exit(EXIT_FAILURE), close(fd));
	data->screen_buffer = ft_calloc(data->width * data->height, sizeof(t_argb));
	data->z_buffer = ft_calloc(data->width * data->height, sizeof(float));
	if (!data->screen_buffer || !data->z_buffer)
		return (close_window(data));
	data->title = ft_strjoin("Wireframe - ", title);
	data->window = mlx_new_window(data->mlx, \
		data->width, data->height, data->title);
	if (!data->window)
		return (close_window(data));
	generate_screen(data);
	data->points = read_file(fd);
	data->mesh = ft_calloc(count_triangles(data->points) + 1, sizeof(t_triangle3));
	if (!data->image || !data->points || !data->mesh)
		return (close_window(data));
	generate_mesh(data->mesh, data->points);
	data->camera = init_camera(data->width, data->height);
	if (!data->camera)
		return (close_window(data));
	ft_memset(&data->lastkey, -1, 6 * sizeof(int));
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf_data	*data;
	int			fd;

	data = ft_calloc(1, sizeof(t_fdf_data));
	if (!data)
		exit(EXIT_FAILURE);
	if (argc != 2)
		return (EXIT_FAILURE);
	if (!try_open_file(&fd, argv[1]))
		return (EXIT_FAILURE);
	if (!check_file(fd))
		return ((void) close(fd), EXIT_FAILURE);
	init_data(data, fd, argv[1]);
	data->camera->moved = 1;
	data->mode = 1;
	start_managers(data);
	mlx_loop(data->mlx);
	return (EXIT_SUCCESS);
}

//cc *.c -Lminilibx-linux -lmlx -lXext -lm -lX11 -Iminilibx-linux -Llibft -lft