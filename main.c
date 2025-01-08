/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:47:15 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/08 18:02:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int	close_window(t_mlx_data *data)
{
	mlx_loop_end(data->mlx);
	mlx_destroy_image(data->mlx, data->image);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->title);
	ft_printf("\033[1;31mEXITING PROGRAM\033[0m\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_manager(int keycode, t_mlx_data	*data)
{
	ft_printf("\033[3;97mKEY RELEASED \033[0m%d\n", keycode);
	if (keycode == XK_Escape)
		return (close_window(data), 0);
	return (0);
}

int	do_loop(t_mlx_data *param)
{
	(void) param;
	return (EXIT_SUCCESS);
}

void	test(void *param)
{
	int	index;
	t_vector3	*lst;

	lst = (t_vector3 *) param;
	index = 0;
	while (lst[index].x != -1)
	{
		ft_printf("| X : %d, Y : %d, Z : %d | ", lst[index].x, lst[index].y, lst[index].z);
		index++;
	}
}

void	*file_to_wireframe(int fd, t_mlx_data *data)
{
	t_list		*file_lines;
	t_image_data img;

	file_lines = read_file(fd);
	ft_lstiter(file_lines, test);
	img.height = 2000;
	img.width = 2000;
	img.connection = data->mlx;
	data->image = mlx_new_image(data->mlx, img.height, img.width);
	img.buffer = mlx_get_data_addr(data->image, &img.pbits, &img.size_line, &img.endian);
	img_set_rectangle(0xABCDEF, make_vec2(500,500), make_vec2(333,333), &img);
	ft_printf("\033[1;92mWIREFRAME GENERATED!\033[0m\n");
	ft_lstclear(&file_lines, free);
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
	data.mlx = mlx_init();
	ft_printf("\033[1;34mGENERATING WIREFRAME...\033[0m\n");
	file_to_wireframe(fd, &data);
	data.title = ft_strjoin("Wireframe - ", argv[1]);
	data.window = mlx_new_window(data.mlx, 2000, 2000, data.title);
	mlx_put_image_to_window(data.mlx, data.window, data.image, 0, 0);
	mlx_key_hook(data.window, key_manager, &data);
	mlx_hook(data.window, DestroyNotify, 0, close_window, &data);
	mlx_loop_hook(data.mlx, do_loop, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
//cc *.c -Lminilibx-linux -lmlx -lXext -lm -lX11 -Iminilibx-linux -Llibft -lft