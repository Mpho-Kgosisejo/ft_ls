/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:49:11 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/03 11:31:49 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*filteroptions(char *argc)
{
	struct s_filteropt fo;

	fo.x = 0;
	fo.options = "lRart";
	fo.ret = ft_strnew(ft_strlen(fo.options));
	while (*argc++ != '\0')
	{
		fo.i = 0;
		fo.found = 0;
		while (fo.options[fo.i] && *argc)
		{
			if (*argc == fo.options[fo.i])
			{
				fo.ret[fo.x] = *argc;
				fo.x++;
				fo.found++;
			}
			fo.i++;
		}
		if (fo.found == 0 && *argc)
			return (NULL);
	}
	return (fo.ret);
}

static char	*get_options(char **argc)
{
	int		i;
	char	*tmp;
	char	*options;

	i = 0;
	options = ft_strnew(1);
	while (argc[i])
	{
		if (argc[i][0] == '-')
		{
			if ((tmp = filteroptions(argc[i])) == NULL)
				return (NULL);
			options = ft_strjoin(options, tmp);
			free(tmp);
		}
		else
			return (options);
		i++;
	}
	return (options);
}

int			main(int argv, char **argc)
{
	char *options;

	options = NULL;
	argc += 1;
	if (argv > 1)
	{
		if ((options = get_options(argc)) == NULL)
		{
			ft_printf("ls: illegal option --\nusage: ls [-Ralrt] [file ...]\n");
			return (-1);
		}
		while (*argc && *argc[0] == '-' && ft_strlen(*argc) >= 2)
			argc++;
	}
	prepare_list(argc, options);
	free(options);
	return (0);
}
