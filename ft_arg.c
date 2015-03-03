/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 11:51:52 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/12 15:42:07 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function bloc handling the creation and sorting of the argument list.
*/

#include "ft_ls.h"

/*
** FT_ARG_LIST |
** ____________|
** Functiong recursively creating the arg_list. it has an unsigned int to
** differ from if there is no argument to if it's the last one. Then calling
** ft_arg_alpha to lexical sort the list.
** PROTYPE VARIABLE
**  > av : the argument list to store in the argument linked list. Only the
**    first element is checked, but next ones are sent recursively to the
**    function.
**  > s : a control size_t to check the size of the previously stored list.
**    Unless equal to 0, will do nothing. On 0, will check if the argument
**    ist is empty, and feed the function with the '.' char.
**  > cr_arg : the current argument to create. By default is set on NULL.
*/
/*
** FT_ARG_ALPHA |
** _____________|
** Function sorting by ASCII order, default sorting function. Will switch
** argument, err and stat structure between two node, the node adress remaining
** the same.
** PROTOTYPE VARIABLE
**  > begin : the first node of the currently inspected linked list. Is used as
**    a "reset" value, if the linked list needs to be checked again after a
**    swap.
**  > tmp : a node used to check and store the node to be compared. Will be
**    incremented recursevily untill NULL is its value, or is superior to the
**    node t, in which case a reset occurs. Default value is the beginning of
**    the list.
**  > t : the other node used to compare, will increment recursively untill its
**    value is NULL, or is inferior to the node tmp, in which case a reset
**    occurs.
** LOCAL VARIABLE
**  > arg : a buffer string to store argument value to be switched.
**  > stt : a buffer struct stat to store stat value to be switched.
**  > err : a buffer int to store error value to be swiched.
*/
/*
** FT_ARG_TIME |
** ____________|
** Function sorting linked list by modification time, given by the struct stat.
** Will switch argument, err and stat structure between two node, the node
** adress remaining the same. Called by checking the CHAR_T bit on the singleton
** returned by ft_parse_sgl(-> ft_parse.c).
** PROTOTYPE VARIABLE
**  > begin : the first node of the currently inspected linked list. Is used as
**    a "reset" value, if the linked list needs to be checked again after a
**    swap.
**  > tmp : a node used to check and store the node to be compared. Will be
**    incremented recursevily untill NULL is its value, or is superior to the
**    node t, in which case a reset occurs. Default value is the beginning of
**    the list.
**  > t : the other node used to compare, will increment recursively untill its
**    value is NULL, or is inferior to the node tmp, in which case a reset
**    occurs.
** LOCAL VARIABLE
**  > arg : a buffer string to store argument value to be switched.
**  > stt : a buffer struct stat to store stat value to be switched.
**  > err : a buffer int to store error value to be swiched.
*/
/*
** FT_ARG_REVOLVE |
** _______________|
** Function recursively revolving the list, calling the singleton to get the o
** ption. To do so it will check the 3rd bit (CHAR_R)  on the char returned by
** the singleton on ft_parse_sgl(-> ft_parse.c).
** PROTYPE VARIABLE
**  > begin : the current list. Since the function is recursively called,
**    the first node depend on the stack state. Once the end of the list is only
**    2 node ahead of the curent first node, will be equal to the adress of
**    buffer node head, which is the node following the current first node.
**  > save : the current first node of the list, used to check the end of the
**    list once the end of the list reached.
**  > head : the head of reading, Default value is NULL but set to the following
**    node after the current first node. Once the NULL value is its next node,
**    its next node becomes the previous one, and by stack effects, revolves the
**    list.
*/
/*
** FT_ARG_DUMP_ERRORS |
** ___________________|
** Function dumping argument list parsing errors, such as the currend node has
** not an existing file name or the acces for the file name on the current node
** is denied. After prompting the error on the dedicaded output, will erase the
** current node and relink the linked list.
** PROTOTYPE VARIABLE
**  > cur : the current linked list. Only the first node is being inspected, but
**    the list recursively parsed. the first node is erased if an error is
**    stored on, and tmp becomes the new first ndoe of the list cur.
**  > tmp : the current second node. Can be equal to NULL. Its existence is used
**    to add another frame on the stack or not.
**  > chip : a control char equal to 0 by default, will increment if errors are
**    met by return of printing functions (-> ft_put.c). Therefore its existence
**    is checked to delete the current node or not, and then will get return
**    value of itself on the frame, and return it.
*/

t_arg	*ft_arg_list(const char **av, const size_t lg, const size_t s, t_arg *cr_arg)
{
	if (s && av && *av && (*av)[0] && (cr_arg = (t_arg*)malloc(sizeof(t_arg))))
	{
		cr_arg->err = 0;
		if ((cr_arg->arg = malloc(ft_strlen(*av) + 1)))
			cr_arg->arg = ft_strcpy(cr_arg->arg, av[0]);
		if ((cr_arg->stt = malloc(sizeof(struct stat))))
			lstat(av[0], cr_arg->stt);
		cr_arg->cr_arg = cr_arg->arg;
		cr_arg->err = errno;
		cr_arg->next = ft_arg_list(av + 1, ft_strlen(av + 1), s + 1, NULL);
	}
	ft_arg_alpha((const t_arg**)&cr_arg, cr_arg, cr_arg);
	return (cr_arg);
}

t_arg	*ft_arg_node(const char *path, const char *av, t_arg *cr_arg)
{
  if (path && av && (cr_arg = (t_arg*)malloc(sizeof(t_arg))))
    {
      cr_arg->err = 0;
      if ((cr_arg->arg = (char*)malloc(ft_strlen(path + 1))))
	cr_arg->arg = ft_strcpy(cr_arg->arg, path);
      if ((cr_arg->stt = malloc(sizeof(struct stat))))
	lstat(av, cr_arg->stt);
      cr_arg->av = cr_arg->arg + (ft_strlen(path) - ft_strlen(av) - 1);
      cr_arg->err = errno;
      cr_arg->next = NULL;
    }
  return (cr_arg);
}
