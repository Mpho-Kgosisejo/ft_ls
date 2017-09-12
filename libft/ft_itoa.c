/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:28:47 by mkgosise          #+#    #+#             */
/*   Updated: 2017/08/13 13:15:53 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getnbr(int nbr)
{
	int i;

	i = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static char	*zero(void)
{
	char *ret;

	ret = ft_strnew(1);
	if (ret == NULL)
		return (NULL);
	ret[0] = '0';
	return (ret);
}

char		*ft_itoa(int n)
{
	int		i;
	int		nbr;
	char	*ret;

	if (n == 0)
		return (zero());
	i = getnbr(ft_abs(n));
	nbr = n;
	if (n < 0)
		i++;
	ret = ft_strnew(i + 1);
	if (ret == NULL)
		return (NULL);
	nbr = ft_abs(n);
	while (nbr != 0)
	{
		i--;
		ret[i] = 48 + (nbr % 10);
		nbr = nbr / 10;
	}
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
