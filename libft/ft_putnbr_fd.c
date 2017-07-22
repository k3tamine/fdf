/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 23:25:35 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 00:40:23 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr_fd(unsigned int n, int fd)
{
	if (n >= 10)
		ft_printnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_printnbr_fd(-n, fd);
	}
	else
		ft_printnbr_fd(n, fd);
}
