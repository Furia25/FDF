/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:36:46 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/12 23:41:50 by val              ###   ########.fr       */
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

typedef struct s_vector4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vect4;

typedef struct s_matrix4
{
    float m[4][4];
}	t_matrix4;

typedef	struct s_quaternion
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quaternion;

typedef struct s_argb
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_argb;

typedef struct s_hsv
{
	float h;
	float s;
	float v;
}	t_hsv;

typedef struct s_triangle
{
	t_vect3	a;
	t_vect3	b;
	t_vect3	c;
}	t_triangle;

typedef struct s_camera
{
	t_matrix4		m_perspective;
	t_matrix4		m_view;
	t_matrix4		m_final;
	t_vect3			pos;
	t_vect3			dir;
	t_vect3			up;
	t_vect3			right;
	int				moved;
	int				width;
	int				height;
	float			spd;
	float			sensivity;
	float			fov;
}	t_camera;

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

typedef struct s_fdf_data
{
	void			*mlx;
	void			*window;
	char			*title;
	void			*image;
	t_image_data	image_data;
	int				height;
	int				width;
	t_list			*points;
	t_triangle		*mesh;
	float			*z_buffer;
	t_argb			*screen_buffer;
	t_camera		*camera;
}	t_fdf_data;

# ifndef M_PI
    # define M_PI 3.14159265358979323846
# endif


/*	Maths Constants	*/
# define TREEHALFS	1.5f
/*	Windows and files Constants	*/
# define FDF_FILE_DELIMITER	' '
# define WINDOW_HEIGHT	1000
# define WINDOW_WIDTH	1000
/*	Drawing Constants	*/
# define CIRCLE_PRECISION 100
# define PERSPECTIVE_FACTOR	50.0f
# define SEGMENT_PRECISION 80
# define SEGMENT_MAXDISTANCE 100
/*	Camera defaults	*/
# define CAMERA_DEFAULT_FOCAL 100
# define CAMERA_DEFAULT_POSITION	(t_vect3){10, 0, 50}
# define CAMERA_DEFAULT_DIR	(t_vect3){0, 0, -1}
# define CAMERA_DEFAULT_UP (t_vect3){0, 1, 0}
# define CAMERA_DEFAULT_SPEED	1
# define CAMERA_DEFAULT_SENSITIVITY 5

void	test(void *param);

t_matrix4		get_perspective_matrix(float fov, float aspect, float near, float far);
t_matrix4		get_view_matrix(t_vect3 cam_pos, t_vect3 dir, t_vect3 right);
t_matrix4		multiply_matrix4(t_matrix4 mat1, t_matrix4 mat2);
t_vect4			project_point_cam(t_vect3 p, t_camera *cam);
t_vect4			vec4_multiply_matrix4(t_matrix4 mat, t_vect4 v);
//
int				is_point_in_cameradir(t_camera *cam, t_vect3 point, float fov);
t_vect3			get_interpolate_3d(t_vect3 p1, t_vect3 p2, float t);
t_vect3			normalize(t_vect3 v);
float			normalize_angle(float angle);
float			fast_sqrt(float number);
//
t_list			*read_file(int fd);
int				try_open_file(int *fd, char *file_path);
int				check_file(int fd);
//
void			set_points(t_list *lst, t_fdf_data *data);
void			*generate_screen(t_fdf_data *data);
//
void			img_draw_screen(t_image_data *img, t_fdf_data *data);
void			img_draw_pixel(t_argb argb, int x, int y, t_image_data *img);
void			img_set_pixel(t_argb color, int x, int y, t_fdf_data *data);
void			img_set_pixel_zbuffer(t_argb color, t_vect4 point, t_fdf_data *data);
void			img_set_circle(t_argb color, t_vect2 coord, int radius, t_fdf_data *data);
void			img_set_disk(t_argb color, t_vect2 cord, int radius, t_fdf_data *data);
void			img_set_point(t_argb color, t_vect4 point, float z, t_fdf_data *data);
void			img_set_segment(t_argb color, t_vect3 a, t_vect3 b, t_fdf_data *data);
//
void			start_managers(t_fdf_data *data);
int				close_window(t_fdf_data *data);
int				key_manager(int keycode, t_fdf_data	*data);
int				do_loop(t_fdf_data *param);
//
t_camera		*init_camera(float wwindow, float hwindow);
t_quaternion    quaternion_normalize(t_quaternion q);
t_quaternion	quaternion_multiply(t_quaternion q1, t_quaternion q2);
t_quaternion	quaternion_conjugate(t_quaternion q);
t_quaternion	quaternion_from_axis_angle(t_vect3 axis, float angle);
void			cam_update_axis(t_camera *cam);
void			cam_update(t_camera *cam);
int				cam_move_forward(float speed, t_camera *cam);
int				cam_move_left(float speed, t_camera *cam);
int				cam_move_up(float speed, t_camera *cam);
int				cam_rotate(t_camera *camera, float yaw, float pitch, float roll);

//
float			dot_product(t_vect3 a, t_vect3 b);
t_vect3			add(t_vect3 a, t_vect3 b);
t_vect3			subtract(t_vect3 a, t_vect3 b);
t_vect3			scale(t_vect3 v, float scalar);
t_vect3			cross_product(t_vect3 a, t_vect3 b);
float			vec3_distance(t_vect3 a, t_vect3 b);
float			vec3_length(t_vect3 v);
t_vect3			vec3_rotate(t_quaternion q, t_vect3 v);
t_vect4			vec3_to_homogeneous(t_vect3 v);
//
t_argb 			hsv_to_argb(t_hsv hsv);
//t_hsv 		argb_to_hsv(t_argb argb);
int				argb_to_int(t_argb argb);
//
void			*memset_fast(void* ptr, int value, size_t num);

#endif