/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/13 11:13:51 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/03 14:49:07 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_sizetab(int *tab, int s)
{
	while (s > 0)
	{
		(tab[s]) = '\0';
		s = s - 1;
	}
	(tab[0]) = 0;
	return (tab);
}

int		ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	size;

	size = 1;
	nb = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
		i++;
	i--;
	while (i >= 0 && '0' <= str[i] && str[i] <= '9')
	{
		nb = nb + ((str[i] - '0') * size);
		size *= 10;
		i--;
	}
	if (str[i] == '-')
		nb = -nb;
	return (nb);
}

char	*ft_strncpy(char *s1, char const *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && s2[i] != '\0')
	{
		s1[i] = s2[i];
		i = i + 1;
	}
	while (i < n)
	{
		s1[i] = '\0';
		i = i + 1;
	}
	return (s1);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*c;
	size_t	t;

	t = 0;
	if (s != NULL)
	{
		if ((c = (char*)malloc(sizeof(len + 1))) == NULL)
			return (NULL);
		while (t < len)
		{
			c[t] = s[start];
			t = t + 1;
			start = start + 1;
		}
		c[t] = '\0';
		return (c);
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			((char*)s)[i] = 0;
			i = i + 1;
		}
	}
}
