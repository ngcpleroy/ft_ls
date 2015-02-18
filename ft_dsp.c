/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 11:39:59 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/18 15:18:40 by nleroy           ###   ########.fr       */
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

const struct t	g_t[9] =
{
	{'-', S_IFREG},
	{'d', S_IFDIR},
	{'c', S_IFCHR},
	{'b', S_IFBLK},
	{'p', S_IFIFO},
	{'l', S_IFLNK},
	{'s', S_IFSOCK},
	{'?', 0},
};

/*
** Semi-Glocal structure linking the st_mode protection mask to the associated
** char to display. POSIX macro gives the authorization for the file for the
** user, the group, and others, as well as the 'sticky' bit, the set-UID bit,
** and the set-gid bit.
*/

const struct tt	g_tt[9] =
{
	{'s', S_IXUSR | S_ISUID, S_IXGRP | S_ISGID, -1},
	{'t', -1, -1, S_IXOTH | S_ISVTX},
	{'r', S_IRUSR, S_IRGRP, S_IROTH},
	{'w', S_IWUSR, S_IWGRP, S_IWOTH},
	{'x', S_IXUSR, S_IXGRP, S_IXOTH},
	{'S', S_ISUID, S_ISGID, -1},
	{'T', -1, -1, S_ISVTX},
	{'-', 0, 0, 0}
};

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

int				ft_dsp_blks(const t_arg *cur, char chip, unsigned int k)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!chip && k < 5)
		i += (f[++k])(cur, 0);
	if ((str = (char*)malloc(i + k)))
	{
	}
}

char	*ft_dsp_refresh_line(const int i)
{
	
}

unsigned char	ft_dsp_blks(const t_arg *cur, const char k, int c,
							unsigned char r)
{
	size_t	s;
	acl_t	acl;

	s = 0;
	s = (k == 0) ? ft_nbrlen(cur->stt->st_nlink) : s;
	s = (k == 1) ? ft_strlen(getpwuid(cur->stt->st_uid)->pw_name) : s;
	s = (k == 2) ? ft_strlen(getgrgid(cur->stt->st_gid)->gr_name) : s;
	s = (k == 3) ? ft_nbrlen(cur->stt->st_size) : s;
	r = ((unsigned char)s > r) ? (unsigned char)s : r;
	if (cur && cur->stt && c >= 0)
		return (ft_eng_blks(cur->next, k, c, r));
	while (c == -1 && r-- > s && k < 4)
		ft_pchar(' ', 1);
	r = (k == 0 && c < 0) ? ft_pnbr_base(cur->stt->st_nlink, 10, 1) : r;
	r = (k == 1 && c < 0) ? ft_pstr(getpwuid(cur->stt->st_uid)->pw_name, 1) : r;
	r = (k == 2 && c < 0) ? ft_pstr(getgrgid(cur->stt->st_gid)->gr_name, 1) : r;
	r = (k == 3 && c < 0) ? ft_pnbr_base(cur->stt->st_size, 10, 1) : r;
	r = (k == 4) ? ft_pstr2((ctime(&cur->stt->st_mtime)), 4, 12, 1) : r;
	if (c < 0 && k == 6 && ((listxattr(cur->arg, NULL, 0, N) > 0)
							|| (acl = acl_get_file(cur->arg, A))))
		c = (acl) ? ft_pchar('+', 1) + acl_free((void*) acl): ft_pchar('@', 1);
	else if (c < 0 && k == 6)
		c = ft_pchar(' ', 1);
	return (r);
}
