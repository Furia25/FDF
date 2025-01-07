/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:36:46 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/07 16:23:56 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include "mlx_int.h"
#include "mlx.h"


#include "./libft/libft.h"
#include "./libft/ft_printf.h"

struct s_mlx_data 
{
	void *mlx;
	void *window;
	char *title;
} typedef t_mlx_data;

#define FDF_FILE_DELIMITER ' '

t_list	*read_file(int fd);
int try_open_file(int *fd, char *file_path);
int	check_file(int fd);


#endif