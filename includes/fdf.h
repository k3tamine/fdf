/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 02:07:16 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/01 16:16:02 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# define WIDTH  1240
# define HEIGHT 670
# define ECHAP	53
# define UP		126
# define DOWN	125
# define RIGHT	124
# define LEFT	123
# define Q		12
# define W		13
# define E		14
# define R		15
# define A		0
# define S		1
# define D		2
# define F		3

typedef struct	s_point
{
	int				x;
	int				y;
	int				z;
	struct s_point	*right;
	struct s_point	*down;
}				t_point;

typedef struct	s_param
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	char			*img_str;
	t_point			*map;
	int				counter;
	int				e;
	int				sx;
	int				sy;
	int				bpp;
	int				size_line;
	int				endian;
	int				space;
	int				x_move;
	int				y_move;
	// int				z_move;
	int				color;
	float			deg;
}				t_param;
t_point			*get_map(int fd);
int				display_map(t_point *point);
int				error_handler(char *err_str);

#endif
