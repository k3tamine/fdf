/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:16:55 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/06 18:03:01 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char		*dest;
	size_t		size;
	size_t		i;

	i = 0;
	size = ft_strlen(str);
	dest = (char *)malloc(sizeof(*dest) * size + 1);
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
