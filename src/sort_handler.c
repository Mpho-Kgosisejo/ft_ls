/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 10:28:41 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/04 11:39:38 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	rev(char **files)
{
	int		i;
	int		x;
	char	*tmp;

	i = 0;
	if ((x = countlist(files)) <= 1)
		return ;
	x--;
	while (i < x && files[i])
	{
		tmp = files[i];
		files[i] = files[x];
		files[x] = tmp;
		i++;
		x--;
	}
}

static void	sort_by_name(char **files, char *options)
{
	ft_sort_2d(files);
	if (ft_strchr(options, 'r'))
		rev(files);
}

static void	sort_by_time(char **files, char *options)
{
	int			i;
	char		*tmp;
	struct stat	st;
	struct stat st1;

	if (!files || countlist(files) <= 1)
		return ;
	i = 1;
	while (files[i])
	{
		if (stat(files[i], &st) >= 0 && stat(files[i - 1], &st1) >= 0)
		{
			if (st.st_mtime > st1.st_mtime)
			{
				tmp = files[i - 1];
				files[i - 1] = files[i];
				files[i] = tmp;
				i = 0;
			}
		}
		i++;
	}
	if (ft_strchr(options, 'r'))
		rev(files);
}

void		sort_handler(char **files, char *options)
{
	if (ft_strchr(options, 't'))
		sort_by_time(files, options);
	else
		sort_by_name(files, options);
}
