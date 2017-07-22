/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 03:23:44 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/20 20:10:26 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int		connect_point(t_point *map)
{
	t_point *line1;
	t_point *line2;

	while (map)
	{
		line1 = map;
		line2 = map->down;
		while (line1 && line2)
		{
			line1->down = line2;
			line1 = line1->right;
			line2 = line2->right;
		}
		map = map->down;
	}
	return (1);
}


static int		get_z(char *str, int *i)
{
	int		n;
	int		z;

	str += *i;
	n = 0;
	if (str[n] == '-')
		n++;
	if (!ft_isdigit(str[n]))
		printf("ERROR\n");
	z = ft_atoi(str);
	while (ft_isdigit(str[n]))
		n++;
	*i += n;
	return (z);
}

static t_point	*new_point(char *str, int *i, int x, int y)
{
	t_point		*output;
	int			z;

	z = get_z(str, i);
	// z = ft_atoi(str);
	if (!(output = (t_point*)ft_memalloc(sizeof(t_point))))
		printf("ERROR\n");
	output->x = x;
	output->y = y;
	output->z = z;
	// printf("x = %d\n", x);
	// printf("y = %d\n", y);
	// printf("z = %d\n", z);
	return (output);
}

static int		read_line(t_point **point, char *str, int y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i])
		{
			*point = new_point(str, &i, x, y);
			point = &((*point)->right);
			x++;
		}
		// printf("point->x = %d\n", (*point)->x);
	}
	return (1);
}

static void		parse_map(int fd, t_point **point)
{
	// 0,82 pour l'iso???
	char	*str;
	int		y;

	y = 0;
	while (get_next_line(fd, &str) == 1)
	{
		read_line(point, str, y);
		// printf("point->x = %d\n", (*point)->x);
		point = &((*point)->down);
		y++;
	}
	if (!y)
		printf("ERROR\n");
}

t_point			*get_map(int fd)
{
	t_point	*map;

	parse_map(fd, &map);
	connect_point(map);
	return (map);
}