/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:09:10 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/14 23:24:18 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = ft_strlen(str);
	while (len && str[len] != c)
		len--;
	if (str[len] == c)
		return ((char *)str + len);
	return (NULL);
}

/*
**int	main()
**{
**	printf("%s\n", ft_strrchr("abcdedcba", 'b'));
**	printf("%s\n", strrchr("abcdedcba", 'b'));
**	return (0);
**}
*/
