/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 15:52:55 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/18 16:01:15 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_format(const t_arg *lst)
{
	char	*str;
	char	c;
	int		i;
	int		j;

	str = NULL;
	i = 0;
	j = 0;
	c = 0;
	while (c < 8)
	{
		i += (f[c])(lst, 0);
		c = c + 1;
	}
	if ((str = (char*)malloc(i + 8)))
		ft_format_fresh(&str, i + 8);
	return (str);
}

void	ft_format_fresh(char **str, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		(*str[i]) = ' ';
		i = i + 1;
	}
	(*str)[max] = '\0';
}
