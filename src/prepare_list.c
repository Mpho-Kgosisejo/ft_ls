/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 15:55:07 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/05 10:51:07 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	path_len(char **paths)
{
	int		i;
	DIR		*dir;

	i = 0;
	while (*paths)
	{
		if ((dir = opendir(*paths)))
		{
			i++;
			closedir(dir);
		}
		paths += 1;
	}
	return (i);
}

static char	**get_validpaths(char **paths)
{
	int		i;
	DIR		*dir;
	char	**ret;

	i = 0;
	if (!(ret = ft_listnew(path_len(paths))))
		return (NULL);
	while (*paths)
	{
		if ((dir = opendir(*paths)))
		{
			ret[i] = ft_strdup(*paths);
			i++;
			closedir(dir);
		}
		else
		{
			ft_putstr("ls: ");
			perror(*paths);
		}
		paths += 1;
	}
	return (ret);
}

static int	files_len(char **paths)
{
	int			i;
	struct stat	st;

	i = 0;
	while (*paths)
	{
		if ((lstat(*paths, &st)) == -1)
		{
			ft_putstr("ls: ");
			perror(*paths);
		}
		else if (!((st.st_mode / 1000) == 16))
			i++;
		paths += 1;
	}
	return (i);
}

static char	**get_validfiles(char **paths)
{
	int			i;
	char		**ret;
	struct stat	st;

	if (!(ret = ft_listnew(files_len(paths))))
		return (NULL);
	i = 0;
	while (*paths)
	{
		if ((stat(*paths, &st)) == -1)
		{
		}
		else if (!((st.st_mode / 1000) == 16))
		{
			ret[i] = ft_strdup(*paths);
			i++;
		}
		paths += 1;
	}
	return (ret);
}

void		prepare_list(char **paths, char *options)
{
	int		i;
	char	*path;
	char	**validpath;
	char	**validfiles;

	if (countlist(paths))
	{
		validfiles = get_validfiles(paths);
		i = 0;
		if (validfiles)
			display_handler(validfiles, options, 1);
		validpath = get_validpaths(paths);
		i = 0;
		if (validpath)
			while (validpath[i])
				recursive_handler(validpath[i++], options);
		ft_free2d((void**)validpath);
	}
	else
	{
		path = ft_strdup(".");
		recursive_handler(path, options);
	}
}
