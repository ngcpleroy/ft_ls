/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 14:33:21 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/18 17:09:26 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_cpt_links(const t_arg *cur, int i)
{
	if (cur)
	{
		i = (ft_nbrlen(cur->stt->st_nlink) > i) ?
			ft_nbrlen(cur->stt->st_nlink) : i;
		i = ft_cpt_links((const t_arg*)cur->next, i);
	}
	return (i);
}

int	ft_cpt_user(const t_arg *cur, int i)
{
	if (cur)
	{
		i = (getpwuid(cur->stt->st_uid) && 
			ft_strlen(getpwuid(cur->stt->st_uid)->pw_name) > i) ?
			ft_strlen(getpwuid(cur->stt->st_uid)->pw_name) : i;
		i = ft_cpt_user((const t_arg*)cur->next, i);
	}
	return (i);
}

int	ft_cpt_group(const t_arg *cur, int i)
{
	if (cur)
	{
		i = (getgrgid(cur->stt->st_gid) && 
			ft_strlen(getgrgid(cur->stt->st_gid)->gr_name) > i) ?
			ft_strlen(getgrgid(cur->stt->st_gid)->gr_name) : i;
		i = ft_cpt_group((const t_arg*)cur->next, i);
	}
	return (i);
}

int ft_cpt_major(const t_arg *cur, int i)
{
	if (cur)
	{
		i = ((S_ISCHR(cur->stt->st_mode) || S_ISBLK(cur->stt->st_mode)) &&
			 ft_nbrlen(major(cur->stt->st_rdev)) + 1 > i ) ?
			ft_nbrlen(major(cur->stt->st_rdev)) + 1 : i;
	}
	return (i);
}

int	ft_cpt_size(const t_arg *cur, int i)
{
	if (cur)
	{
		i = (ft_nbrlen(cur->stt->st_size) > i) ?
			ft_nbrlen(cur->stt->st_size) : i;
		i = ((S_ISCHR(cur->stt->st_mode) || S_ISBLK(cur->stt->st_mode)) &&
			 ft_nbrlen(minor(cur->stt->st_rdev)) > i ) ?
		i = ft_cpt_size((const t_arg*)cur->next, i);
	}
	return (i);
}
