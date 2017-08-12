/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:22:27 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/12 14:55:38 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_error(char *err_str)
{
	ft_putendl_fd(err_str, 2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	int		fd;
	t_point	*map;

	if (ac != 2)
		handle_error("2 arguments expected\nUsage : ./fdf <filename>");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		handle_error("Error : Can't open file");
	map = get_map(fd);
	display_map(map);
	close(fd);
	return (0);
}
