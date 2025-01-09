/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:36:46 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/10 00:25:12 by val              ###   ########.fr       */
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
	t_vect3	euler;
	t_vect3	up;
	t_vect3	right;
	int		moved;
	float	spd;
	float	sensivity;
}	t_camera;

typedef struct s_fdf_data
{
	void		*mlx;
	void		*window;
	char		*title;
	void		*image;
	int			height;
	int			width;
	t_list		*points;
	t_camera	*camera;
}	t_fdf_data;

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
# define WINDOW_HEIGHT	1000
# define WINDOW_WIDTH	1000
/*	Drawing Constants	*/
# define CIRCLE_PRECISION 100
# define PERSPECTIVE_FACTOR	30.0f
# define SEGMENT_PRECISION 10
/*	Camera defaults	*/
# define CAMERA_DEFAULT_FOCAL 90
# define CAMERA_DEFAULT_POSITION	(t_vect3){10, 10, 50}
# define CAMERA_DEFAULT_DIR	(t_vect3){0, 0, -1}
# define CAMERA_DEFAULT_EULERDIR	(t_vect3){0, 0, 0}
# define CAMERA_DEFAULT_UP (t_vect3){0, 1, 0}
# define CAMERA_DEFAULT_SPEED	1
# define CAMERA_DEFAULT_SENSITIVITY 0.5
# define CAMERA_DEFAULT_SENSFACTOR 20

t_vect3		get_interpolate_3d(t_vect3 p1, t_vect3 p2, float t)
t_vect3		project_point_cam(t_vect3 point, float f, t_camera *cam, t_fdf_data *data);
t_vect3		normalize(t_vect3 v);
float		normalize_angle(float angle);
//
t_list		*read_file(int fd);
int			try_open_file(int *fd, char *file_path);
int			check_file(int fd);
//
void		*generate_wireframe(t_fdf_data *data);
//
void		img_set_rect(int color, t_vect2 co, t_vect2 size, t_image_data *img);
void		img_set_pixel(int color, t_vect2 coord, t_image_data *img);
void		img_draw_circle(int color, t_vect2 coord, int radius, t_image_data *img);
void		img_draw_zdistpoint(int color, t_vect3 point, t_image_data *img);
//
void		start_managers(t_fdf_data *data);
int			close_window(t_fdf_data *data);
int			key_manager(int keycode, t_fdf_data	*data);
int			do_loop(t_fdf_data *param);
//
t_camera	*init_camera(void);
void		cam_update_axis(t_camera *cam);
void		cam_update(t_camera *cam);
int			cam_move_forward(float speed, t_camera *cam);
int			cam_move_left(float speed, t_camera *cam);
int			cam_move_up(float speed, t_camera *cam);
int			cam_rotate_left(float sensitivity, t_camera *cam);
int			cam_rotate_up(float sensitivity, t_camera *cam);
//
float		dot_product(t_vect3 a, t_vect3 b);
t_vect3		add(t_vect3 a, t_vect3 b);
t_vect3		subtract(t_vect3 a, t_vect3 b);
t_vect3		scale(t_vect3 v, float scalar);
t_vect3		cross_product(t_vect3 a, t_vect3 b);

#endif