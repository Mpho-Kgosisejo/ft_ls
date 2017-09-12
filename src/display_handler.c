/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:37:43 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/04 17:31:28 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*catfile_details(struct s_fdetails *fds)
{
	int		len;
	char	*ret;

	len = ft_strlen(fds->prem);
	len += ft_strlen(fds->nlnks);
	len += ft_strlen(fds->psdname);
	len += ft_strlen(fds->grpname);
	len += ft_strlen(fds->size);
	len += ft_strlen(fds->mtime);
	len += 6;
	ret = ft_strnew(len);
	ft_strcpy(ret, fds->prem);
	ft_strcat(ret, "?");
	ft_strcat(ret, fds->nlnks);
	ft_strcat(ret, "?");
	ft_strcat(ret, fds->psdname);
	ft_strcat(ret, "?");
	ft_strcat(ret, fds->grpname);
	ft_strcat(ret, "?");
	ft_strcat(ret, fds->size);
	ft_strcat(ret, "?");
	ft_strcat(ret, fds->mtime);
	return (ret);
}

static char	*final_file(char *path)
{
	struct s_fdetails	fds;
	struct group		*grp;
	struct passwd		*pswd;
	struct stat			st;

	if (stat(path, &st) == -1)
		return (NULL);
	if (!(grp = getgrgid(st.st_gid)))
		return (NULL);
	if (!(pswd = getpwuid(st.st_uid)))
		return (NULL);
	fds.prem = get_permission(path);
	fds.nlnks = ft_itoa(st.st_nlink);
	fds.psdname = ft_strdup(pswd->pw_name);
	fds.grpname = ft_strdup(grp->gr_name);
	fds.size = ft_itoa((int)st.st_size);
	fds.mtime = ft_strsub(ctime(&st.st_mtime), 4, 12);
	return (catfile_details(&fds));
}

static void	display(char **names, char **details)
{
	int			i;
	char		**tmp;
	char		*item;
	struct stat	st;

	i = 0;
	while (names[i])
	{
		tmp = ft_strsplit(details[i], '?');
		lstat(names[i], &st);
		ft_printf("%s ", tmp[0]);
		ft_printf("%s ", (item = ft_precision(1, details, tmp[1])));
		ft_printf("%s ", (item = ft_precision(2, details, tmp[2])));
		ft_printf("%s ", (item = ft_precision(3, details, tmp[3])));
		ft_printf("%s ", (item = ft_precision(4, details, tmp[4])));
		ft_printf("%s ", (item = ft_precision(5, details, tmp[5])));
		ft_putstr(get_filename(names[i]));
		if (S_ISLNK(st.st_mode))
			display_link(names[i]);
		ft_putendl("");
		ft_free2d((void**)tmp);
		i++;
	}
}

static void	long_list(char **files, int is_direct)
{
	struct s_long_list	sll;

	sll.i = 0;
	sll.block_size = 0;
	sll.final_files = ft_listnew(0);
	while (files[sll.i])
	{
		if (lstat(files[sll.i], &sll.st) == 0)
		{
			sll.block_size += sll.st.st_blocks;
			sll.ftmp = final_file(files[sll.i]);
			sll.tmp = ft_listcat(sll.final_files, sll.ftmp);
			ft_free2d((void**)sll.final_files);
			free(sll.ftmp);
			sll.final_files = sll.tmp;
		}
		sll.i++;
	}
	if (countlist(files) && !is_direct)
		ft_printf("total %i\n", sll.block_size);
	display(files, sll.final_files);
	ft_free2d((void**)sll.final_files);
}

void		display_handler(char **files, char *options, int is_direct)
{
	int		i;

	if (!files || !countlist(files))
		return ;
	i = 0;
	sort_handler(files, options);
	if (ft_strchr(options, 'l'))
		long_list(files, is_direct);
	else
		while (files[i])
			ft_putendl(get_filename(files[i++]));
	ft_free2d((void**)files);
}
