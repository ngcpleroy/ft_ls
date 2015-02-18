/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 11:19:11 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/11 16:57:10 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Main function bloc, calling the option parser/creator, then
** creating and sorting the argument list, to finally execute the
** display / dynamic list generation on the argument list.
*/

#include "ft_ls.h"

/*
** MAIN |
** _____|
** Main function, calling parse option to 'fill' ac with bits, storing it in a
** singleton, then creating from what's left of the av an arg-list. Calling then
** the engine function (-> ft_engine.c) on the argument.
**  > ac : the number of arguments, including the program name. Converted to
**    char to store options bit masks from ft_parse_option, and then sent back
**    to ft_parse_sgl to store the options on a singleton.
**  > av : the arguments list, read on ft_parse_option (-> ft_parse.c) to get
**    options and invalid options, then used to generate argument linked list on
**  > ft_arg_list (-> ft_arg.c).
*/

int	main(int ac, char **av)
{
	t_arg	*arg_list;

	arg_list = NULL;
	if ((ac = (char)ft_parse_option((const char**)(++av), 0, 0)) < 0)
		return (ft_pendl("Error : wrong argument type", 2));
	while (av && av[0] && av[0][0] && av[0][1] && av[0][0] == '-'
		&& (av[0][1] == 'a' || av[0][1] == 'l' || av[0][1] == 'r'
			|| av[0][1] == 'R' || av[0][1] == 't'))
		av += 1;
	ft_parse_sgl((char)ac);
	arg_list = (av && *av) ? ft_arg_list((const char **)av, 1, ft_strlen(av), NULL) 
		: ft_arg_list((const char **)".", 0, 1, NULL);
	ft_arg_dump_errors(&arg_list, arg_list->next, 0);
	ft_arg_time((const t_arg**)&arg_list, arg_list, arg_list);
ft_pnbr_base(__LINE__, 10, 1);
ft_pendl(__FUNCTION__, 1);
ft_pendl("", 1);
	ft_eng_launch(&arg_list, 0, NULL, NULL);
ft_pnbr_base(__LINE__, 10, 1);
ft_pendl(__FUNCTION__, 1);
ft_pendl("", 1);
	return (0);
}
