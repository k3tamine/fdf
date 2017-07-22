/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 01:54:39 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 02:20:13 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_isblank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static size_t		ft_blank_nb(const char *s, size_t *begin, size_t *end)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (ft_isblank(s[i++]))
		*begin += 1;
	if (*begin == len)
		return (0);
	while (ft_isblank(s[len - 1]))
	{
		*end += 1;
		len--;
	}
	return (len - *begin);
}

char				*ft_strtrim(char const *s)
{
	char	*ret_str;
	size_t	begin;
	size_t	end;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	begin = 0;
	end = 0;
	i = 0;
	len = ft_blank_nb(s, &begin, &end);
	ret_str = (char *)malloc(sizeof(*ret_str) * len + 1);
	if (!ret_str)
		return (NULL);
	while (i < len)
		ret_str[i++] = s[begin++];
	ret_str[i] = '\0';
	return (ret_str);
}
