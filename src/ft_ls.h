/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 15:07:30 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/05 10:56:04 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <time.h>
# include <stdio.h>
# include <sys/xattr.h>

struct	s_filteropt
{
	int		i;
	int		x;
	int		found;
	char	*ret;
	char	*options;
};

struct	s_dodir
{
	char			*fpath;
	char			**dfiles;
	char			**catdir;
	DIR				*dir;
	struct dirent	*dst;
	struct stat		st;
};

struct	s_long_list
{
	int			i;
	int			block_size;
	char		**tmp;
	char		**final_files;
	char		*ftmp;
	struct stat	st;
};

struct	s_fdetails
{
	char	*prem;
	char	*nlnks;
	char	*psdname;
	char	*grpname;
	char	*size;
	char	*mtime;
};

void	prepare_list(char **paths, char *options);
void	recursive_handler(char *path, char *options);
void	display_handler(char **files, char *options, int is_direct);
void	sort_handler(char **files, char *options);
void	do_recursive(char **paths, char *options);
void	display_link(char *path);
void	set_2d_dodir(char ***arr1, char ***arr2);
void	show_error_dodir(char *path);

char	*get_permission(char *file_path);
char	*get_filename(char *path);
char	*ft_precision(int index, char **strs, char *word);

#endif
