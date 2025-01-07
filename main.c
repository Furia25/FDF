/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:47:15 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/07 16:47:09 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int	close_window(t_mlx_data *data)
{
	mlx_loop_end(data->mlx);
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

int do_loop(t_mlx_data *param)
{
	(void) param;
	//printf("test : %p \n", param->mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	t_list		*file_lines;
	int			fd;
	//int			**test;
	
	if (argc != 2)
		return (EXIT_FAILURE);
	if (!try_open_file(&fd, argv[1]))
		return (EXIT_FAILURE);
	if (!check_file(fd))
		return ((void) close(fd), EXIT_FAILURE);
	file_lines = read_file(fd);
	
	//test = parse_file(file_lines);
	//ft_printf("%d", file_lines->next->next->content + 2);
	//ft_lstiter(file_lines, (void *) ft_printf);
	data.mlx = mlx_init();
	data.title = ft_strjoin("Wireframe - ", argv[1]);
	data.window = mlx_new_window(data.mlx, 2000, 2000, data.title);
	mlx_key_hook(data.window, key_manager, &data);
	mlx_hook(data.window, DestroyNotify, 0, close_window, &data);
	mlx_loop_hook(data.mlx, do_loop, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
//cc *.c -Lminilibx-linux -lmlx -lXext -lm -lX11 -Iminilibx-linux -Llibft -lft