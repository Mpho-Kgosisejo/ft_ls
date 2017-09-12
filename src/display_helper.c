/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 12:18:27 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/05 10:58:14 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	fill_permission(int perm, char *str)
{
	if (perm == 1)
		str[2] = 'x';
	else if (perm == 2)
		str[1] = 'w';
	else if (perm == 3)
		ft_strncpy(&str[0], "wx", 2);
	else if (perm == 4)
		str[0] = 'r';
	else if (perm == 5)
	{
		str[0] = 'r';
		str[2] = 'x';
	}
	else if (perm == 6)
		ft_strncpy(&str[0], "rw", 2);
	else if (perm == 7)
		ft_strncpy(&str[0], "rwx", 3);
}

char		*get_permission(char *fpath)
{
	int			num;
	char		*ret;
	struct stat	st;

	lstat(fpath, &st);
	ret = ft_strnew(11);
	ft_memset(ret, '-', 10);
	ret[10] = ' ';
	if (S_ISDIR(st.st_mode))
		ret[0] = 'd';
	else if (S_ISLNK(st.st_mode))
		ret[0] = 'l';
	if (listxattr(fpath, NULL, 0, XATTR_NOFOLLOW) > 0)
		ret[10] = '@';
	num = ft_atoi(ft_itoa_base(st.st_mode, 8));
	num = num % 1000;
	fill_permission((num / 100), &ret[1]);
	fill_permission(((num / 10) % 10), &ret[4]);
	fill_permission((num % 10), &ret[7]);
	return (ret);
}

void		display_link(char *path)
{
	int		rd;
	char	buff[1096];

	if ((rd = readlink(path, buff, sizeof(buff))) > 0)
	{
		buff[rd] = 0;
		ft_putstr(" -> ");
		ft_putstr(buff);
	}
}

char		*get_filename(char *path)
{
	char *fn;

	if ((fn = ft_strrchr(path, '/')))
	{
		if ((fn = &ft_strrchr(path, '/')[1]))
			return (fn);
	}
	return (path);
}
