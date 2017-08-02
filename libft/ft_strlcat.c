/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:50:21 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/16 10:22:15 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (dst[i] && i < size)
		i++;
	len = i;
	while (src[i - len] && i < size - 1)
	{
		dst[i] = src[i - len];
		i++;
	}
	if (len < i)
		dst[i] = '\0';
	return (len + ft_strlen(src));
}
