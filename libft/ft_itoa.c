/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 20:57:06 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 00:37:08 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_calculate_size(int nb, int sign)
{
	int	size;

	size = 1;
	while (nb / 10 * sign >= 1)
	{
		size++;
		nb /= 10;
	}
	return (sign < 0) ? size + 1 : size;
}

char			*ft_itoa(int n)
{
	size_t	i;
	size_t	size;
	int		sign;
	char	*res;

	sign = (n < 0) ? -1 : 1;
	size = ft_calculate_size(n, sign);
	res = (char *)malloc(sizeof(*res) * size + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (sign == -1)
		res[i++] = '-';
	res[size] = '\0';
	while (i < size)
	{
		res[size - 1] = n % 10 * sign + '0';
		n /= 10;
		size--;
	}
	return (res);
}
