/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:10:34 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 01:07:59 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (((char *)src)[i] == c)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
			return (dest + i);
		}
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (NULL);
}
