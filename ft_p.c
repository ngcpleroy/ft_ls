/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 15:00:25 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/18 11:08:44 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_pchar(const char c, const int fd)
{
	if (write(fd, &c, 1) >= 0)
		return (1);
	return (0);
}

char	ft_pstr(const char *argv, const int fd)
{
	unsigned int	u;

	u = 0;
	while (argv[u])
		u = u + ft_pchar(argv[u], fd);
	if (argv[u])
		return (0);
	return (1);
}

char	ft_pendl(const char *argv, const int fd)
{
	if (ft_pstr(argv, fd) && ft_pchar('\n', fd))
		return (1);
	return (0);
}

char	ft_pnbr_base(const long n, const int base, const int fd)
{
	long		start;
	long		end;
	const char	base_str[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (n < 0)
	{
		ft_pchar('-', fd);
		ft_pnbr_base(-n, base, fd);
	}
	else
	{
		end = n % base;
		start = (n - end) / base;
		if (start != 0)
			ft_pnbr_base((const long)start, base, fd);
		ft_pchar(base_str[end], fd);
	}
	return (1);
}

char	ft_pstr2(const char *argv, const int fd, size_t s, const size_t e)
{
	while (e && argv[s] && s <= e)
		s = s + ft_pchar(argv[s], fd);
	while (!e && argv[s])
		s = s + ft_pchar(argv[s], fd);
	if (argv[s])
		return (0);
	return (1);
}
