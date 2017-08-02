/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 17:16:59 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/02 12:57:28 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	init_params(t_param *params)
{
	params->space = WIDTH / 150;
	params->deg = 0.5;
	params->x_move = 0;
	params->y_move = 0;
	params->color = 0x00f23452;
	params->img_ptr = NULL;
}

static int	key_hook(int keycode, t_param *params)
{
	if (keycode == ECHAP)
		exit(EXIT_SUCCESS);
	else if (keycode == Q)
		params->deg += 0.05;
	else if (keycode == W)
		params->space += WIDTH / 1000;
	else if (keycode == S)
		params->space -= WIDTH / 1000;
	else if (keycode == LEFT)
		params->x_move -= 10;
	else if (keycode == RIGHT)
		params->x_move += 10;
	else if (keycode == UP)
		params->y_move -= 10;
	else if (keycode == DOWN)
		params->y_move += 10;
	else if (keycode == E)
		params->color += 30;
	handle_img(params);
	return (0);
}

int			display_map(t_point *map)
{
	void	*img_ptr;
	t_param	params;

	init_params(&params);
	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WIDTH, HEIGHT, "fdf");
	params.map = map;
	handle_img(&params);
	mlx_hook(params.win, 2, 1, key_hook, &params);
	mlx_loop(params.mlx);
	return (0);
}
