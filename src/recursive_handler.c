/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 11:58:19 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/05 10:59:40 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	**listcat_helper(char **dir, char *path, int is_dir)
{
	char **tmp;

	tmp = NULL;
	if ((ft_strcmp(ft_strrchr(path, '/'), "/..") == 0 ||
				ft_strcmp(ft_strrchr(path, '/'), "/.") == 0) && is_dir)
		return (dir);
	if (!(tmp = ft_listcat(dir, path)))
		return (NULL);
	ft_free2d((void**)dir);
	return (tmp);
}

static void	dodir(char *path, char *options, struct s_dodir sd)
{
	if (!(sd.dir = opendir(path)))
		return (void)show_error_dodir(path);
	set_2d_dodir(&sd.catdir, &sd.dfiles);
	while ((sd.dst = readdir(sd.dir)))
		if (stat(sd.fpath = ft_strjoinpath(path, sd.dst->d_name), &sd.st) == 0)
		{
			if (ft_strchr(options, 'a'))
			{
				sd.dfiles = listcat_helper(sd.dfiles, sd.fpath, 0);
				if (S_ISDIR(sd.st.st_mode))
					sd.catdir = listcat_helper(sd.catdir, sd.fpath, 1);
			}
			else
			{
				if (sd.dst->d_name[0] != '.')
				{
					sd.dfiles = listcat_helper(sd.dfiles, sd.fpath, 0);
					if (S_ISDIR(sd.st.st_mode))
						sd.catdir = listcat_helper(sd.catdir, sd.fpath, 1);
				}
			}
		}
	closedir(sd.dir);
	display_handler(sd.dfiles, options, 0);
	do_recursive(sd.catdir, options);
}

void		do_recursive(char **dir, char *options)
{
	int				i;
	struct s_dodir	sd;

	if (!dir || !countlist(dir))
		return ;
	if (!ft_strchr(options, 'R'))
		return ;
	sort_handler(dir, options);
	i = 0;
	while (dir[i])
	{
		sd.dir = NULL;
		ft_putchar('\n');
		ft_putstr(dir[i]);
		ft_putendl(":");
		dodir(dir[i], options, sd);
		i++;
	}
	ft_free2d((void**)dir);
}

void		recursive_handler(char *path, char *options)
{
	struct s_dodir	sd;

	sd.dir = NULL;
	dodir(path, options, sd);
}
