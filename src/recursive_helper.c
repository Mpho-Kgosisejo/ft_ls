/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkgosise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:53:47 by mkgosise          #+#    #+#             */
/*   Updated: 2017/09/05 10:58:16 by mkgosise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	show_error_dodir(char *path)
{
	ft_putstr("ls: ");
	perror(path);
}

void	set_2d_dodir(char ***arr1, char ***arr2)
{
	*arr1 = ft_listnew(0);
	*arr2 = ft_listnew(0);
}
