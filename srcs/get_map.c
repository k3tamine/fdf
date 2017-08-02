/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 03:23:44 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/02 12:39:21 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

static t_point	*new_point(char *str, int *i, int x, int y)
{
	t_point		*point;
	int			n;
	int			z;

	str += *i;
	n = 0;
	z = ft_atoi(str);
	while (str[n] != ' ' && str[n])
		n++;
	*i += n;
	if (!(point = (t_point*)ft_memalloc(sizeof(t_point))))
		handle_error("Error : Malloc failed, not enough space?");
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
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
	}
	return (1);
}

static void		parse_map(int fd, t_point **point)
{
	char	*str;
	int		y;

	y = 0;
	while (get_next_line(fd, &str) == 1)
	{
		read_line(point, str, y);
		point = &((*point)->down);
		y++;
	}
	if (!y)
		handle_error("Error : File is empty");
}

t_point			*get_map(int fd)
{
	t_point	*map;

	parse_map(fd, &map);
	connect_point(map);
	return (map);
}
