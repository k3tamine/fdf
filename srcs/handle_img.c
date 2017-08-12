/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 12:27:34 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/12 13:09:10 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void		fill_pixel(int x, int y, int color, t_param *params)
{
	int	pos;
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (color & 0x00ff0000) >> 16;
	green = (color & 0x0000ff00) >> 8;
	blue = (color & 0x000000ff);
	alpha = 0;
	if (y > 0 && y < WIDTH)
	{
		pos = y * WIDTH * 4 + x * 4;
		if (pos > 0 && pos < (HEIGHT * WIDTH * 4))
		{
			params->img_str[pos] = blue;
			params->img_str[pos + 1] = green;
			params->img_str[pos + 2] = red;
			params->img_str[pos + 3] = alpha;
		}
	}
}

static void		link_2points(t_param *params, t_point p1, t_point p2, int color)
{
	int x;
	int y;

	x = labs(p2.x - p1.x);
	y = labs(p2.y - p1.y);
	params->sx = (p1.x < p2.x) ? 1 : -1;
	params->sy = (p1.y < p2.y) ? 1 : -1;
	params->counter = (x > y) ? (x / 2) : -(y / 2);
	while (p1.x != p2.x || p1.y != p2.y)
	{
		if (p1.x > 0 && p1.x < WIDTH)
			fill_pixel(p1.x, p1.y, color, params);
		params->e = params->counter;
		if (params->e > -x)
		{
			params->counter = params->counter - y;
			p1.x = p1.x + params->sx;
		}
		if (params->e < y)
		{
			params->counter = params->counter + x;
			p1.y = p1.y + params->sy;
		}
	}
}

static t_point	calculate_iso(t_param params, t_point point)
{
	long	x;
	long	y;

	x = WIDTH / 2 + point.x
		* params.space * cos(params.deg) - point.y
		* params.space * cos(params.deg) + params.x_move;
	y = HEIGHT / 2 + point.x
		* params.space * sin(params.deg) + point.y * params.space
		* sin(params.deg) - point.z * params.space + params.y_move;
	point.x = x;
	point.y = y;
	return (point);
}

static void		fill_image(t_param *params, t_point *map)
{
	t_point *first;

	first = map;
	while (map)
	{
		while (map)
		{
			params->p1 = calculate_iso(*params, *map);
			if (params->p1.x > 0 && params->p1.x < WIDTH)
				fill_pixel(params->p1.x, params->p1.y, params->color, params);
			if (map->right)
			{
				params->p2 = calculate_iso(*params, *(map)->right);
				link_2points(params, params->p1, params->p2, params->color);
			}
			if (map->down)
			{
				params->p2 = calculate_iso(*params, *(map)->down);
				link_2points(params, params->p1, params->p2, params->color);
			}
			map = map->right;
		}
		first = first->down;
		map = first;
	}
}

void			handle_img(t_param *params)
{
	if (params->img_ptr)
		mlx_destroy_image(params->img_ptr, params->img_str);
	params->img_ptr = mlx_new_image(params->mlx, WIDTH, HEIGHT);
	params->img_str =
	mlx_get_data_addr(
	params->img_ptr, &(params->bpp), &(params->size_line), &(params->endian));
	fill_image(params, params->map);
	mlx_put_image_to_window(params->mlx, params->win, params->img_ptr, 0, 0);
	mlx_string_put(params->mlx, params->win, 10, 10, 0xFFFFFF,
					"Q = Rotation");
	mlx_string_put(params->mlx, params->win, 10, 30, 0xFFFFFF,
					"W = Increase size");
	mlx_string_put(params->mlx, params->win, 10, 50, 0xFFFFFF,
					"S = Decrease size");
	mlx_string_put(params->mlx, params->win, 10, 70, 0xFFFFFF,
					"E = Change Color");
}
