/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:37:56 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/14 22:43:48 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	to_find;
	unsigned char	*str;

	str = (unsigned char *)s;
	to_find = (unsigned char)c;
	while (n--)
	{
		if (*str == to_find)
			return (str);
		str++;
	}
	return (NULL);
}
