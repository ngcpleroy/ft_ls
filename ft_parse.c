/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 11:05:29 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/10 17:18:35 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function bloc handling the option generation and option getter.
*/

#include "ft_ls.h"

/*
** Globale structure inside this bloc only, describing the option, macro in
** header
*/

const struct t	g_ti[5] =
{
	{'a', CHAR_A},
	{'l', CHAR_L},
	{'r', CHAR_R},
	{'R', CHAR_RR},
	{'t', CHAR_T}
};

/*
** FT_PARSE_OPTION |
** ________________|
** Function filling a char with bits, since only 5 option are availables,
** 31 max shall be its value.
** PROTOTYPE VARIABLE
**  > av : the argument list to be inspected. will only check first argument but
**    will call recursively the other ones, untill finding none/improper option
**    format
**  > i : counter to what character is being inspected on the argument.
**    Increments on everycall
**  > r : return value, he gets his value from the bits mask defined by the semi
**    global structure g_t.
** LOCAL VARIABLE
**  > k : incremental value to check the g_t array structure.
*/
/*
** FT_PARSE_SGL |
** _____________|
** Function 'singleton' that, at 1st call, creates a char static, then for every
** other call, will return this char. An elegant way to create a global without
** creating one.
** PROTOTYPE VARIABLE
**  > value : a control char. Unless negative, gives the value to store.
**    Negative, returns the stored value.
** LOCAL VARIABLE
**  > opt : a static char used as a singleton to return the options stored on
**    first call.
*/

char	ft_parse_option(const char **av, const unsigned int i, char r)
{
	int	k;

	k = 0;
	if (av && av[0])
	{
		if (!av[0][i])
			return (ft_parse_option(av + 1, 0, r));
		else if (av[0][i] == '-' && i == 0)
			return (ft_parse_option(av, 1, r));
		else if (i)
		{
			while (k < 5 && av[0][i] != g_ti[k].c)
				k++;
			if (k >= 5)
				return (-1);
			return (ft_parse_option(av, i + 1, r | g_ti[k].flag));
		}
		else if (av[0][0] != '-')
			return ((char)r);
	}
	return ((char)r);
}

char	ft_parse_sgl(const char value)
{
	static char	opt = 0;

	opt = (value >= 0) ? value : opt;
	return (opt);
}
