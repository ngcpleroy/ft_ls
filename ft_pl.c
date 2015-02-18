/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 16:03:30 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/18 17:19:05 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_pl_links(const t_arg *cur, char **str, int end)
{
	int				i;
	unsigned int	cpy;

	i = ft_nbrlen(cur->stt->st_nlink);
	j = 0;
	cpy = cur->stt->st_nlink;
	while (cpy != 0)
	{
		(*cur)[end - j] = (char)((cpy % 10) + '0');
		j++;
		cpy = cpy / 10;
	}
	return (1);
}

char	ft_pl_user(const t_arg *cur, char **str, int end)
{
	int	i;
	int j;

	i = (getpwuid(cur->stt->st_uid)) ? 
		end - ft_strlen(getpwuid(cur->stt->st_uid)->pw_name) : 0;
	j = 0;
	while (getpwuid(cur->stt->st_uid) 
		   && (getpwuid(cur->stt->st_uid)->pw_name)[j])
	{
		(*cur)[i + j] = getpwuid(cur->stt->st_uid)->pw_name[j];
		j++;
	}
	return (1);
}

char	ft_pl_group(const t_arg *cur, char **str, int start)
{
	int	i;
	int j;

	i = (getgrgid(cur->stt->st_uid)) ? 
		end - ft_strlen(getgrgid(cur->stt->st_uid)->gr_name) : 0;
	j = 0;
	while (getgrgid(cur->stt->st_uid) 
		   && (getgrgid(cur->stt->st_uid)->gr_name)[i])
	{
		(*cur)[i + j] = getgrgid(cur->stt->st_uid)->gr_name[i];
		j++;
	}
	return (1);
}

char	ft_pl_major(const t_arg *cur, char **str, int start)
{
	int				j;
	unsigned int	cpy;

	cpy = (S_ISCHR(cur->stt->st_mode) || S_ISBLK(cur->stt->st_mode)) ?
		ft_nbrlen(major(cur->stt->st_mode)) : 0;
	j = 0;
	while (cpy != 0)
	{
		(*cur)[end - j] = (j != 0) ? (char)((cpy % 10) + '0') : ',';
		cpy = (j != 0) ? cpy / 10 : cpy;
		j++;
	}
	return (1);
}

char	ft_pl_size(const t_arg *cur, char **str, int start)
{
	int				j;
	unsigned int	cpy;

	cpy = (S_ISCHR(cur->stt->st_mode) || S_ISBLK(cur->stt->st_mode)) ?
		ft_nbrlen(minor(cur->stt->st_mode)) : cur->stt->st_size;
	j = 0;
	while (cpy != 0)
	{
		(*cur)[end - j] = (char)((cpy % 10) + '0');
		j++;
		cpy = cpy / 10;
	}
	return (1);
}
