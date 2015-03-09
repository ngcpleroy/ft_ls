/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 11:39:59 by nleroy            #+#    #+#             */
/*   Updated: 2015/03/09 13:28:06 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Display engine. Takes a list as parameter, and display asked informations.
*/

#include "ft_ls.h"

/*
** Global structure linking the st_mode protection mask to the associated char
** to display. POSIX macro gives the file type, which is an octal int.
*/

/*
** Semi-Glocal structure linking the st_mode protection mask to the associated
** char to display. POSIX macro gives the authorization for the file for the
** user, the group, and others, as well as the 'sticky' bit, the set-UID bit,
** and the set-gid bit.
*/

unsigned char	ft_dsp_blks_init(const t_arg *cur, const char k, const char)

char			ft_dsp_file(const t_arg *l, ssize_t k, char c, char *a)
{
	static unsigned char	blk[5];

	while (k < 4 && l && !l->err && c >= 0)
		blk[k] = (c == 0) ? ft_eng_blks(l, k, (k % 3 + 1) >> 1, 0) : blk[k];
	c = (c >= 0) ? 0 : -1;
	while ((k = 0) && c < 10 && c >= 0 && l && !l->err)
	{
		while (k < 7 && !((l->stt->st_mode & g_t[k].flag && c == 0) || (!(l
->stt->st_mode & g_tt[k].f1) && c < 4) || (!(l->stt->st_mode & g_tt[k].f2) &&
	c >= 4 && c < 7) || (!(l->stt->st_mode & g_tt[k].f3) && c >= 7 && c < 10)))
			k++;
		c += (c >= 0) ? ft_pchar(g_tt[k].c, 1) : ft_pchar(g_t[k].c, 1);
	}
	if (c >= 0)
		ft_eng_blks(l, 6, -1, 0);
	while (c >= 0 && l && !l->err && k++ < 5 && ft_parse_sgl(-1) & CHAR_L)
		c = ft_eng_blks((const t_arg*)l, k, -1, blk[k - 1]) + ft_pchar(' ', 1);
ft_pnbr_base(ft_parse_sgl(-1) & 1, 10, 1);
ft_pendl("", 1);
ft_pendl(l->arg, 1);
ft_pnbr_base(__LINE__, 10, 1);
ft_pendl(__FUNCTION__, 1);
ft_pendl("", 1);
k = (ft_parse_sgl(-1) & 1 || l->arg[l->lg] != '.') ? ft_pstr2(l->arg, l->lg, 1) : 0;
	if (l && !l->err && l->stt->st_mode & S_IFLNK && c >= 0 &&
		(a = malloc(sizeof(char) * readlink(l->arg, NULL, 0) + 1)) &&
		(k = readlink(l->arg, a, sizeof(a))) &&
		(a[k] = '\0') && ft_pstr(" -> ", 1) && ft_pendl(a, 1) && (a))
		free(a);
	c = (l->next) ? ft_eng_file(l->next, 0, c, NULL) : 0;
	return (0);
}
