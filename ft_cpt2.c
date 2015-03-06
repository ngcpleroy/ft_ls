/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 15:19:06 by nleroy            #+#    #+#             */
/*   Updated: 2015/03/06 11:08:43 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_cpt_time(const t_arg *cur, int i)
{
	if (cur)
		i = 14;
	return (i);
}

int	ft_cpt_name(const t_arg *cur, int i)
{
	if (cur)
	{
		i = (ft_strlen(cur->arg) - cur->lg > i) ? 
			ft_strlen(cur->arg) - cur->lg : i;
		i = ft_cpt_user((const t_arg*)cur->next, i);
	}
	return (i);

}

int ft_cpt_link(const t_arg *cur, int i)
{
	if (cur)
	{
		i = (S_ISLNK(l->stt->st_mode)) ? readlink(cur->arg, NULL, 0) + 4 : i;
		i = ft_cpt_link((const t_arg*)cur->next, i);
	}
	return (i);
}
