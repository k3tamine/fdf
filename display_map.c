/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 17:16:59 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/26 02:29:29 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		init_params(t_param *params)
{
	params->space = WIDTH / 150;
	params->deg = 0.5;
	params->alpha = 0;
	params->x_move = 0;
	params->y_move = 0;
	params->img_ptr = NULL;
}

static void		fill_pixel(int x, int y, int color, t_param *params)
{
	int	pos;

	params->red = (color & 0x00ff0000) >> 16;
	params->green = (color & 0x0000ff00) >> 8;
	params->blue = (color & 0x000000ff);
	if (y > 0 && y < WIDTH)
	{
		pos = y * WIDTH * 4 + x * 4;
		if (pos > 0 && pos < (HEIGHT * WIDTH * 4))
		{
			params->img_str[pos] = params->blue;
			params->img_str[pos + 1] = params->green;
			params->img_str[pos + 2] = params->red;
			params->img_str[pos + 3] = params->alpha;
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
				link_2points(params, p1, p2, 0x000080BB);
			p2 = calculate_iso(*params, *(map)->down);
			if (map->down->down)
				link_2points(params, p1, p2, 0x000080BB);
			map = map->right;
		}
		map = first->down;
		first = first->down;
	}
}

static void		handle_image(t_param *params)
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

static int		key_hook(int keycode, t_param *params)
{
	if (keycode == ECHAP)
		exit(0);
	else if (keycode == Q)
		params->deg += 0.1;
	else if (keycode == A)
		params->deg -= 0.1;
	else if (keycode == W)
		params->space += WIDTH / 350;
	else if (keycode == S)
		params->space -= WIDTH / 350;
	else if (keycode == LEFT)
		params->x_move -= 100;
	else if (keycode == RIGHT)
		params->x_move += 100;
	else if (keycode == UP)
		params->y_move -= 100;
	else if (keycode == DOWN)
		params->y_move += 100;
	handle_image(params);
	printf("key = %d\n", keycode);
	return (0);
}

int				display_map(t_point *map)
{
	void	*img_ptr;
	t_param	params;

	init_params(&params);
	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WIDTH, HEIGHT, "fdf");
	params.map = map;
	handle_image(&params);
	mlx_key_hook(params.win, key_hook, &params);
	// mlx_loop_hook(params.mlx, key_hook, &params);
	mlx_loop(params.mlx);
	return (0);
}
