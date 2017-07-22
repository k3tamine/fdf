/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:22:27 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/19 17:15:19 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//POUR ROTATION
//X = x0*cos(a) - y0*sin(a)
//Y = x0*sin(a) + yo*cos(a)
//https://openclassrooms.com/forum/sujet/passer-de-3d-a-2d-mathematiques-12239
//http://www.sciences.ch/htmlfr/geometrie/geometrieprojective01.php

// int	key_hook(int keycode, t_mlx *mlx_d)
// {
// 	if (keycode == ECHAP)
// 		exit(1);
// 	printf("key event %d\n", keycode);
// 	mlx_pixel_put(mlx_d->mlx, mlx_d->win, 300, 300, 0xFF00FF);
// 	return (1);
// }

// int	draw(t_mlx *mlx_d)
// {
// 	int	x;
// 	int	y;

// 	y = 50;
// 	while (y++ < 200)
// 	{
// 		x = 50;
// 		while (x++ < 200)
// 			mlx_pixel_put(mlx_d->mlx, mlx_d->win, x, y, 0x00FFFFFF);
// 	}
// 	return (1);
// }

// int	expose_hook(t_mlx *mlx_d)
// {
// 	draw(mlx_d);
// 	return (1);
// }

// int	main()
// {
// 	void	*mlx;
// 	void	*win;
// 	t_mlx	mlx_d;
// 	int		x;
// 	int		y;

// 	if (!(mlx_d.mlx = mlx_init()))
// 		return (0);
// 	// if (!(mlx_d = (t_mlx)malloc(sizeof(mlx_d))))
// 		// return (0);
// 	mlx_d.win = mlx_new_window(mlx_d.mlx, WIDTH, HEIGHT, "mlx 42");
// 	mlx_expose_hook(mlx_d.win, expose_hook, &mlx_d);
// 	mlx_key_hook(mlx_d.win, key_hook, &mlx_d);
// 	mlx_loop(mlx_d.mlx);
// 	return (0);
// }


int	main(int ac, char **av)
{
	int		fd;
	t_point	*map;

	if (ac != 2)
		printf("ERROR nb params\n");
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		printf("ERROR fail open\n");
		return (1);
	}
	map = get_map(fd);
	display_map(map);
	close(fd);
	return (0);
}
