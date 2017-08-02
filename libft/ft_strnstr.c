/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:10:45 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 20:28:31 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack[i] && !needle[i])
		return ((char *)haystack);
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && needle[j] && i + j < len)
			j++;
		if (!needle[j])
			return ((char *)haystack + i);
		else
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
