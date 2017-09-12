/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_size_ls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 16:55:19 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/02 16:07:23 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_precision(int indx, char **strs, char *word)
{
	int		i;
	int		l;
	char	*tmp;
	char	*tmp2;
	char	**details;

	l = 0;
	i = 0;
	while (strs[i])
	{
		details = ft_strsplit(strs[i], '?');
		if ((int)ft_strlen(details[indx]) > l)
			l = ft_strlen(details[indx]);
		ft_free2d((void**)details);
		i++;
	}
	tmp = ft_itoa(l);
	tmp2 = ft_strjoin("@", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, ".@");
	free(tmp2);
	tmp2 = precision(tmp, word);
	return (tmp2);
}
