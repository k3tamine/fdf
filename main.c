/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:22:27 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/01 16:30:08 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

//POUR ROTATION
//X = x0*cos(a) - y0*sin(a)
//Y = x0*sin(a) + yo*cos(a)
//https://openclassrooms.com/forum/sujet/passer-de-3d-a-2d-mathematiques-12239
//http://www.sciences.ch/htmlfr/geometrie/geometrieprojective01.php

// POUR TONTON
// DECLARATION DE params COMME ACTUELLEMENT OU MALLOC???

int	error_handler(char *err_str)
{
	ft_putendl_fd(err_str, 2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	int		fd;
	t_point	*map;

	if (ac != 2)
		error_handler("2 arguments expected\nUsage : ./fdf <filename>");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		error_handler("Error : Can't open file");
	map = get_map(fd);
	display_map(map);
	close(fd);
	return (0);
}
