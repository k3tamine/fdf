/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:23:48 by mgonon            #+#    #+#             */
/*   Updated: 2016/11/15 00:38:08 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_calculate_w(char const *str, int *w_nb, int *w_max_size, char c)
{
	int	i;
	int	tmp;

	i = 0;
	while (str[i])
	{
		tmp = 0;
		while (str[i] == c)
			i++;
		if (str[i])
			*w_nb += 1;
		while ((str[i] != c) && str[i])
		{
			i++;
			tmp++;
		}
		if (tmp > *w_max_size)
			*w_max_size = tmp;
	}
}

static char	**ft_feed_array(char const *str, char **tab, int j, char c)
{
	int		k;
	int		i;

	i = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] == c)
			i++;
		if (!str[i])
		{
			tab[j] = 0;
			return (tab);
		}
		while ((str[i] != c) && str[i])
			tab[j][k++] = str[i++];
		tab[j][k] = '\0';
		j++;
		if (!str[i])
		{
			tab[j] = 0;
			return (tab);
		}
	}
	return (tab);
}

char		**ft_strsplit(char const *str, char c)
{
	int		w_nb;
	int		w_max_size;
	int		i;
	char	**tab;

	if (!str)
		return (NULL);
	w_nb = 0;
	w_max_size = 0;
	i = 0;
	ft_calculate_w(str, &w_nb, &w_max_size, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (w_nb + 1))))
		return (NULL);
	while (i <= w_nb)
	{
		if (!(tab[i] = (char *)malloc(sizeof(**tab) * (w_max_size + 1))))
			return (0);
		i++;
	}
	if (!*str)
		*tab = 0;
	else
		tab = ft_feed_array(str, tab, 0, c);
	return (tab);
}
