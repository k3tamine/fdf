/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 07:42:30 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/06 19:06:39 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		feed_line(char **stock, char **line)
{
	char	*tmp;
	int		diff;

	if (ft_strchr(*stock, '\n'))
		diff = ft_strlen(*stock) - ft_strlen(ft_strchr(*stock, '\n'));
	else
		diff = ft_strlen(*stock);
	*line = ft_strsub(*stock, 0, diff);
	if (ft_strchr(*stock, '\n'))
	{
		tmp = ft_strdup(ft_strchr(*stock, '\n') + 1);
		free(*stock);
		*stock = ft_strdup(tmp);
		free(tmp);
	}
	else
		*stock[0] = '\0';
	return (1);
}

int		feed_stock(char **stock, int fd)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	ret = 1;
	while (!(ft_strchr(*stock, '\n')) && (ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		if (**stock)
		{
			tmp = ft_strdup(*stock);
			free(*stock);
			*stock = ft_strjoin(tmp, buff);
			free(tmp);
		}
		else
			*stock = ft_strjoin(*stock, buff);
	}
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static char	*stock = "";

	if (fd < 0 || !line || BUFF_SIZE < 0)
		return (-1);
	if (feed_stock(&stock, fd) < 0)
		return (-1);
	if (stock[0] == '\0')
	{
		*line = NULL;
		return (0);
	}
	if (feed_line(&stock, line) < 0)
		return (-1);
	return (1);
}
