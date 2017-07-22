/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 01:47:34 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/10 00:53:34 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret_str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret_str = (char *)malloc(sizeof(*ret_str) * len + 1);
	if (!ret_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ret_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ret_str[j++] = s2[i++];
	ret_str[j] = '\0';
	return (ret_str);
}
