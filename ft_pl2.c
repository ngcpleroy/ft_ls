/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pl2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 16:01:59 by nleroy            #+#    #+#             */
/*   Updated: 2015/03/09 16:30:09 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


char	ft_pl_time(const t_arg *cur, char **str, int end)
{
	int		i;
	time_t	now;
	
	i = 4;
	now = time(NULL);
	while ((i <= 10 && cur->stt->st_mtime) || (i <= 15 && cur->stt->st_mtime
		&& (cur->stt->st_mtime - now >= 15778463 
			|| cur->stt->st_mtime - now <= -15778463)))
    {
		*str[end - (16 - i + 4)] = *(ctime(&(*cur->stt).st_mtime) + i);
		i++;
    }
	while (i <= 15 && (cur->stt->st_mtime - now >= 15778463
					   || cur->stt->st_mtime - now <= -15778463))
    {
		str[end - (14 - i)] = (i == 11) ? ' ' 
			: *(ctime(&(*cur->stt).st_mtime) + i + 8);
		i++;
    }
}

char	ft_pl_name(const t_arg *cur, char **str, int end)
{
	int	i;
	int	j;
  
	i = (cur->av) ? end - ft_strlen(cur->av) : 0;
	j = 0;
	while (cur->av && cur->av[j])
    {
		(*str)[i + j] = cur->av[j];
		j++;
    }
	return (1);
}

char	ft_pl_link(const t_arg *cur, char **str, int end)
{
	if (cur && S_ISLNK(cur->stt->st_mode))
    {
		while (*str[end] == ' ')
			end--;
		*str[end++] = ' ';
		*str[end++] = '-';
		*str[end++] = '>';
		*str[end++] = ' ';
		readlink(cur->arg, *str + end, readlink(cur->arg, NULL, 0));
    }
	return (1);
}
