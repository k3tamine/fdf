/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 01:10:16 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/07 01:57:16 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret_str;
	int		i;

	if (s)
	{
		ret_str = (char *)malloc(sizeof(*ret_str) * ft_strlen(s) + 1);
		if (!ret_str)
			return (NULL);
		i = 0;
		while (s[i])
		{
			ret_str[i] = f(s[i]);
			i++;
		}
		ret_str[i] = '\0';
		return (ret_str);
	}
	return (NULL);
}
