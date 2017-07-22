/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:27:03 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 00:18:52 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*s1;
	char	*s2;

	if (dst < src)
		return (ft_memcpy(dst, src, n));
	if (dst > src)
	{
		s1 = (char *)dst;
		s2 = (char *)src;
		while (n--)
			s1[n] = s2[n];
		return (s1);
	}
	return (dst);
}
