/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 23:03:27 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 00:37:37 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr(unsigned int n)
{
	if (n >= 10)
		ft_printnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void		ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		ft_printnbr(-n);
	}
	else
		ft_printnbr(n);
}
