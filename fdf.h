/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:36:46 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/08 18:39:36 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <X11/Xlib.h>
# include <X11/keysymdef.h>
# include "mlx_int.h"
# include "mlx.h"
# include "./libft/libft.h"
# include "./libft/ft_printf.h"
# include <math.h>

typedef	struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef	struct s_vector3
{
	int	x;
	int	y;
	int	z;
}	t_vector3;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*window;
	char		*title;
	void		*image;
	t_vector3	camera;
}	t_mlx_data;

typedef struct s_image_data
{
	void		*connection;
	int			height;
	int			width;
	int			pbits;
	int			size_line;
	int			endian;
	char		*buffer;
}	t_image_data;


# define FDF_FILE_DELIMITER	' '
# define GET_PIXEL(x, y, size)	(y * size) + (x * 4)

t_list	*read_file(int fd);
int		try_open_file(int *fd, char *file_path);
void	img_set_pixel(int color, t_vector2 coord, t_image_data *img);
void	img_set_rectangle(int color, t_vector2 coord, t_vector2 size, t_image_data *img);
t_vector2	make_vec2(int x, int y);
t_vector3	make_vec3(int x, int y, int z);
int		check_file(int fd);

#endif