/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:43:19 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/04 15:02:30 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_2d(char **arr)
{
	int		i;
	char	*tmp;

	if (!arr || countlist(arr) <= 1)
		return ;
	i = 1;
	while (arr[i])
	{
		if (ft_strcmp(arr[i - 1], arr[i]) > 0)
		{
			tmp = arr[i - 1];
			arr[i - 1] = arr[i];
			arr[i] = tmp;
			i = 0;
		}
		i++;
	}
}
