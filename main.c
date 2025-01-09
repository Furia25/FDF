/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:47:15 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/09 18:52:09 by val              ###   ########.fr       */
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

void	generate_points(t_list *lst, t_image_data *img, t_mlx_data *data)
{
	int		index;
	t_vect3	*array;
	t_vect3	point;

	while (lst)
	{
		array = (t_vect3 *) lst->content;
		index = 0;
		while (array[index].x != -1)
		{
			point = project_point_cam(array[index], 2, data);
			printf("%f %f \n", point.x, point.y);
			img_draw_zdistpoint(0xABCDEF, point, img);
			index++;
		}
		lst = lst->next;
	}
}

void	*generate_wireframe(t_mlx_data *data)
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
	generate_points(data->points, &img, data);
	return (data->image);
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	int			fd;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (!try_open_file(&fd, argv[1]))
		return (EXIT_FAILURE);
	if (!check_file(fd))
		return ((void) close(fd), EXIT_FAILURE);
	data.height = 1000;
	data.width = 1000;
	data.camera = (t_vect3){25, 25, -50};
	data.camera_dir = normalize((t_vect3){0, 0, -1});
	data.image = NULL;
	data.mlx = mlx_init();
	data.title = ft_strjoin("Wireframe - ", argv[1]);
	ft_printf("\033[1;34mGENERATING WIREFRAME...\033[0m\n");
	data.points = read_file(fd);
	ft_printf("\033[1;92mWIREFRAME GENERATED!\033[0m\n");
	data.window = mlx_new_window(data.mlx, data.width, data.height, data.title);
	data.camera_moved = 1;
	start_managers(&data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
//cc *.c -Lminilibx-linux -lmlx -lXext -lm -lX11 -Iminilibx-linux -Llibft -lft