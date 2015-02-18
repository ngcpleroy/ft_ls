/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:39:53 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/11 12:55:35 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s != NULL && s[0])
	{
		while (s[i] && s[i] != c)
			i = i + 1;
		if (s[i - 1] && s[i - 1] == c)
			return ((char*)s + (i - 1));
		else if (s[i] == c)
			return ((char*)s + i);
		return (NULL);
	}
	return (NULL);
}

char	*ft_strcpy(char *s1, char const *s2)
{
	unsigned int	i;

	i = 0;
	while (s2 && s2[i])
	{
		s1[i] = s2[i];
		i = i + 1;
	}
	s1[i] = '\0';
	while (s1[i])
		s1[i++] = '\0';
	return (s1);
}

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if ((tmp = (char*)malloc(sizeof(n))) == NULL)
		return (NULL);
	while (i != n)
	{
		tmp[i] = ((char*)s2)[i];
		i = i + 1;
	}
	i = 0;
	while (i != n)
	{
		((char*)s1)[i] = tmp[i];
		i = i + 1;
	}
	free(tmp);
	return (s1);
}

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char*)s1)[i] = ((char*)s2)[i];
		i = i + 1;
	}
	return ((void*)s1);
}
