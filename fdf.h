/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 02:07:16 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/21 02:44:00 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
// # define WIDTH  2560
// # define HEIGHT 1440
# define WIDTH  1240
# define HEIGHT 670
# define RATIO_X 20
# define RATIO_Y 20
# define RATIO_Z 2
# define ECHAP	53
# define UP		126
# define DOWN	125
# define RIGHT	124
# define LEFT	123
# define ZOOM   6
# define DEZOOM 7

typedef struct	s_param
{
	void			*mlx;
	void			*win;
	int				x_min;
	int				y_min;
	int				x_max;
	int				y_max;
	int				ratio_x;
	int				ratio_y;
	int				width;
	int				height;
	//TODEL
	int				counter;
	int				e;
	int				sx;
	int				sy;
	int				bits_pp;
	int				size_line;
	int				endian;
	char    		*my_img_str;
	void			*img_ptr;
}				t_param;

typedef struct	s_point
{
	int				x;
	int				y;
	int				z;
	int				x_size;
	int				y_size;
	struct s_point	*right;
	struct s_point	*down;
}				t_point;

// t_point			*parse_map(int fd);
t_point			*get_map(int fd);
int				display_map(t_point *point);

#endif
