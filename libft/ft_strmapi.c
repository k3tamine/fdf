/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 01:31:44 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/07 01:33:31 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*ret_str;
	unsigned int		i;

	if (s)
	{
		ret_str = (char *)malloc(sizeof(*ret_str) * ft_strlen(s) + 1);
		if (!ret_str)
			return (NULL);
		i = 0;
		while (s[i])
		{
			ret_str[i] = f(i, s[i]);
			i++;
		}
		ret_str[i] = '\0';
		return (ret_str);
	}
	return (NULL);
}
