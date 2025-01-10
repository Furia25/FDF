/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:47:15 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/10 18:23:04 by val              ###   ########.fr       */
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
		printf("| X : %f, Y : %f, Z : %f | ", lst[index].x,);
		index++;
	}
} */

void	generate_points(t_list *lst, t_image_data *img)
{
	int		index;
	t_vect3	*array;
	t_vect3	*temp;
	t_argb 	color;

	while (lst)
	{
		array = (t_vect3 *) lst->content;
		index = -1;
		while (array[++index].x != -1)
		{
			if (!is_point_in_cameradir(img->data->camera, array[index], img->data->camera->fov))
				continue;
			color = (t_argb){0, 0, 0, 0};
			if (array[index + 1].x != -1)
				img_draw_segment(color, array[index], array[index + 1], img);
			if (lst->next)
			{
				temp = (t_vect3 *) lst->next->content;
				img_draw_segment(color, array[index], temp[index], img);
			}
		}
		lst = lst->next;
	}
}

void	*generate_wireframe(t_fdf_data *data)
{
	t_image_data	img;

	img.data = data;
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
	generate_points(data->points, &img);
	return (data->image);
}

int	init_data(t_fdf_data *data, int fd, char *title)
{
	data->width = WINDOW_WIDTH;
	data->height = WINDOW_HEIGHT;
	data->image = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		close(fd);
		exit(EXIT_FAILURE);
		return(1);
	}
	data->title = ft_strjoin("Wireframe - ", title);
	data->window = mlx_new_window(data->mlx, data->width, data->height, data->title);
	if (!data->window)
		return (close_window(data));
	data->points = read_file(fd);
	data->camera = init_camera();
	if (!data->camera)
		return (close_window(data));
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
	start_managers(data);
	t_quaternion q_90_z = quaternion_from_axis_angle((t_vect3){0, 0, 1}, 90);
	printf("Quaternion: %f %f %f %f\n", q_90_z.w, q_90_z.x, q_90_z.y, q_90_z.z);

	t_vect3 v_rotated = vec3_rotate(q_90_z, (t_vect3){1, 0, 0});
	printf("Rotated Vector: %f %f %f\n", v_rotated.x, v_rotated.y, v_rotated.z);
	mlx_loop(data->mlx);
	return (EXIT_SUCCESS);
}

//cc *.c -Lminilibx-linux -lmlx -lXext -lm -lX11 -Iminilibx-linux -Llibft -lft