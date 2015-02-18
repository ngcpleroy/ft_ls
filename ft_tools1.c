/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 14:35:49 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/11 16:42:03 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*ft_strdup(const char *src)
{
	size_t	i;
	char	*srccpy;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if ((srccpy = (char*)malloc(sizeof(len + 1))) == NULL)
		ft_pendl("Memory allocation failed", 2);
	else
	{
		while (i <= len + 1)
		{
			srccpy[i] = '\0';
			i = i + 1;
		}
		i = 0;
		while (src && src[i])
		{
			srccpy[i] = src[i];
			i = i + 1;
		}
		return (srccpy);
	}
	return (NULL);
}

size_t			ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
		i = i + 1;
	return (i);
}

unsigned int	ft_nbrlen(const long l)
{
	long		s;
	int			i;

	i = 1;
	s = 1;
	while (s * 10 <= l)
	{
		i++;
		s *= 10;
	}
	return i;
}

int				ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1 && s2 && s1[i] > s2[i])
		return (s1[i] - s2[i]);
	else if (s1 && s2 && s1[i] < s2[i])
		return (s1[i] - s2[i]);
	else
		return (0);
}

char			*ft_strdir(const char *s1, const char *s2)
{
	size_t	s;
	size_t	tmp;
	char	*ret;

	tmp = 0;
	s = ft_strlen(s1) + ft_strlen(s2) + 2;
	ret = NULL;
	if (s1 && s2 && s && (ret = malloc(s)))
	{
		while (tmp < ft_strlen(s1))
		{
			ret[tmp] = s1[tmp];
			tmp++;
		}
		ret[tmp] = '/';
		tmp = tmp + 1;
		while (tmp - 1 - ft_strlen(s1) <= ft_strlen(s2))
		{
			ret[tmp] = s2[tmp - 1 - ft_strlen(s1)];
			tmp = tmp + 1;
		}
		while (tmp <= s)
		{
			ret[tmp] = '\0';
			tmp++;
		}
	}
	return (ret);
}
