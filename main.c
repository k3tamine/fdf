/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:22:27 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/26 02:26:32 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//POUR ROTATION
//X = x0*cos(a) - y0*sin(a)
//Y = x0*sin(a) + yo*cos(a)
//https://openclassrooms.com/forum/sujet/passer-de-3d-a-2d-mathematiques-12239
//http://www.sciences.ch/htmlfr/geometrie/geometrieprojective01.php

// POUR TONTON
// DECLARATION DE params COMME ACTUELLEMENT OU MALLOC???

int	main(int ac, char **av)
{
	int		fd;
	t_point	*map;

	if (ac != 2)
	{
		printf("ERROR nb params\n");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		printf("ERROR fail open\n");
		return (2);
	}
	map = get_map(fd);
	display_map(map);
	close(fd);
	return (0);
}
