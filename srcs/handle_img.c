/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 12:27:34 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/02 12:39:21 by mgonon           ###   ########.fr       */
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

	x = abs(p2.x - p1.x);
	y = abs(p2.y - p1.y);
	params->sx = (p1.x < p2.x) ? 1 : -1;
	params->sy = (p1.y < p2.y) ? 1 : -1;
	params->counter = (x > y) ? (x / 2) : -(y / 2);
	while (1)
	{
		fill_pixel(p1.x, p1.y, color, params);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
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
	int		x;
	int		y;

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
	t_point	p1;
	t_point	p2;

	first = map;
	while (map->down)
	{
		while (map->right)
		{
			p1 = calculate_iso(*params, *map);
			p2 = calculate_iso(*params, *(map)->right);
			if (map->right->right)
				link_2points(params, p1, p2, params->color);
			p2 = calculate_iso(*params, *(map)->down);
			if (map->down->down)
				link_2points(params, p1, p2, params->color);
			map = map->right;
		}
		map = first->down;
		first = first->down;
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
}
