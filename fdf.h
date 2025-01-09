/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:36:46 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/09 19:25:52 by val              ###   ########.fr       */
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

typedef struct s_vector2
{
	float	x;
	float	y;
}	t_vect2;

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vect3;

typedef struct s_camera
{
	t_vect3	pos;
	t_vect3	dir;
	t_vect3	up;
	int		moved;
	float	spd;
	float	sensivity;
}	t_camera;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*window;
	char		*title;
	void		*image;
	int			height;
	int			width;
	t_list		*points;
	t_camera	camera;
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
/*	Drawing Constants	*/
# define CIRCLE_PRECISION 100
# define PERSPECTIVE_FACTOR	10.0f
/*	Camera defaults	*/
# define CAMERA_DEFAULT_POSITION	(t_vect3){25, 25, -50}
# define CAMERA_DEFAULT_DIR	(t_vect3){0, 0, -1}
# define CAMERA_DEFAULT_SPEED	0.01
# define CAMERA_DEFAULT_SENSITIVITY 0.01

t_vect3		get_interpolate_3d(t_vect3 p1, t_vect3 p2, float t);
t_vect3		project_point_cam(t_vect3 point, float focalLength, t_mlx_data *data);
t_vect3		normalize(t_vect3 v);
//
t_list		*read_file(int fd);
int			try_open_file(int *fd, char *file_path);
int			check_file(int fd);
//
void		*generate_wireframe(t_mlx_data *data);
//
void		img_set_rect(int color, t_vect2 co, t_vect2 size, t_image_data *img);
void		img_set_pixel(int color, t_vect2 coord, t_image_data *img);
void		img_draw_zdistpoint(int color, t_vect3 point, t_image_data *img);
//
void		start_managers(t_mlx_data *data);
int			close_window(t_mlx_data *data);
int			key_manager(int keycode, t_mlx_data	*data);
int			do_loop(t_mlx_data *param);
//
float		dot_product(t_vect3 a, t_vect3 b);
t_vect3		add(t_vect3 a, t_vect3 b);
t_vect3		subtract(t_vect3 a, t_vect3 b);
t_vect3		scale(t_vect3 v, float scalar);
t_vect3		cross_product(t_vect3 a, t_vect3 b);

#endif