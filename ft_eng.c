/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eng.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 14:46:33 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/18 11:52:32 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Engine bloc, running on arguments the different options.
*/

#include "ft_ls.h"

/*
**  FT_ENG_LAUNCH |
**  ______________|
** Function lauching the 'engine', main function running this program. Will at
** first call split the argument list between directories and everything else.
** Then it will give the list 'files' to display (and erase if the control char
** erase exists) at 1st call, else it will display without erase the list
** list. After this a backtrack occurs : the function will create a list
** from the current arg of the list if it's a directory, and recurively will
** send it to itself on another frame, if the R option is found on the singleton
** on ft_parse_sgl (-> ft_parse.c). Otherwise, the current node will be deleted
** and set to NULL. If no node is found on the lsit but it still exist, the list
** itself is deleted and set to NULL.
** PROTOTYPE VARIABLE *
**  > list : the argument list, at 1st call is build by valid arguments set
**    as parameters of the program. If the engine is called recursively, will
**    contain a list of the current directory to be displayed.
**  > chip : a control char to indicate 1st call.
**  > files : Wether and empty list to be filled with files given in the
**    list, or a copy of arg list to be displayed but not erased. On the
**    while loop, will change its value if the R option is found of the
**    singleton to the list of the current directory given by the node cur
** LOCAL VARIABLE *
**  > cur : a node set to the currend node of the list list being parsed.
**    change its value along the list, then is deleted.
*/
/*
** FT_ENG_PARSE_FILES |
** ___________________|
** Function checking for files on the current first node of the list, and if
** found moves them to the first current node of a seperated list. Therefore by
** stacking effect, will create a new list.
** PROTOTYPE VARIABLE *
**  > cur : the current list. At ech frame moves to the current address of the
**    second node of the list.
**  > tmp : the second node of the list. Can be equall to NULL. Is mainly used
**    to recursively parse the list, also to relink directories list.
**  > chip : control character. Use to check wether or not the file is a
**    directory.
**  > files : the current non-directory list. Default value is NULL, and is
**    affected to each non-null non directory node. If no affectation occurs,
**    then is sent back to the next call of the function.
*/
/*
** FT_ENG_PARSE_DIR |
** _________________|
** Function creating a argument list and returning, by stack effect, the total
** size of his elements. At first call, will open a dir with the opendir
** function, and then call itself. All other frames on the stack untill the end
** of the directory's read-end will create a t_arg node from the current dirent
** d_name with the function ft_arg_list (-> ft_arg.c).
** Once the end of the directory is reached, the DIR is closed, and the
** stack unwraps, returning the size of the current node added with the previous
** node size on the stack. Once the first frame is reached, the list is sorted
** by ft_arg_time (-> ft_arg.c).
** PROTOTYPE VARIABLE *
**  > cur : a t_arg node giving at 1st call the directory to work on. Its
**    existence is used as a chack value to determine what action to take.
**    Unless empty, the current frame of stack is the 1st one.
**  > list : a t_arg node send by adress to fill. Default value is NULL. It is
**    then created by ft_arg_list along with the name of the current file given
**    by the struct dirent.
**  > dir : the current DIR repertory being open. At 1st call is NULL, then set
**    to the dir associated with the argument contained in the t_arg node cur.
**    Is recursively read to give the struct dirent dirent to the other frame of
**    stack, and is closed on the frame where end of reading is reached.
**  > dirent : a dirent structure giving the current file to be created. Only
**    his d_name is checked.
** LOCAL VARIABLE *
**  > total_size : a size_t used as a return value to give the total current
**    size of the list. Since the lsit is being created on the stack, will
**    will increment on each returned frame of the function.
*/
/*
** FT_ENG_FILES |
** _____________|
** Function diplaying all informations required. Given a t_arg node, the spaces
** between each -l option information are being computed, and stored into an
** array. Then the protection status, ACL and extended attribute, and link
** status are being computed and display. If the -l is not present, only the
** file name is displayed, unless it begins with a '.' and -a option is absent.
** Then recursively called on the next node.
** PROTOTYPE VARIABLE
**  > l : the current node of the linked list to be displayed.
**  > k : control char, used to increment g_t and g_tt structure, also used as
**    incremental value for the blanks array giving numbers of space to dusplay
**    between rows.
**  > c : chip control char, incrementing as the function goes. if he is
**    equal to 0 during return, problem occured and an error is displayed.
**  > lk is used as a buffer for the readlink function, to properly diplay the
**    name of the linked file, by default equall to NULL.
** LOCAL VARAIBLE*
**  > blk : array storing max spaces to display, computed by the ft_eng_blks
**    function.
*/
/*
** FT_ENG_BLKS |
**_____________|
** Fonction computing number of blanks to put between each output of an -l
** option line and printing the number of hard links, user, group and size of
** a give object, with the proper blanks to be displayed for it to be aligned.
** PROTOTYPE VARIABLE *
**  > cur : the current node of the linked list to be displayed, or its space
**    to be computed.
**  > k : a control char giving either used as the kth case of the blanks array
**    to be filled, or the (k + 1)th information to be printed. On a value of 5,
**    will display time.
**  > c : a control char giving the kind of operation to execute on the return
**    char. either it's used as checking value to know the maximum size of a
**    number, or a null control char to compute the size of a string, or a
**    negative control char to print the (k + 1)th information.
**  > r : the return char value, used to either give the proper number of max
**    spaces to be printed on the k-th case of the array, or the control chip to
**    check print return value.
** LOCAL VARIABLE *
**  > s : a incremental value to help computing a number literal length.
*/

char			ft_eng_launch(t_arg **l, char chip, t_arg **files, t_arg *cur)
{
ft_pnbr_base(__LINE__, 10, 1);
ft_pendl(__FUNCTION__, 1);
ft_pendl("", 1);
	if (l && *l)
	{
ft_pnbr_base(__LINE__, 10, 1);
ft_pendl(__FUNCTION__, 1);
ft_pendl("", 1);
		if (!chip)
			chip = (!chip) ? ft_eng_parse_files(l, (*l)->next, 0, files) : 1;
		chip = (!chip && files) ? ft_eng_launch(files, 1, files, NULL) : chip;
		chip += (files) ? ft_eng_file((const t_arg *)*files, 0,
								(CHAR_L & ft_parse_sgl(-1)) - 1, NULL) : 0;
		while (l && *l && (cur = (*l)))
		{
			cur = *l;
			if ((ft_parse_sgl(-1) & CHAR_RR || !chip) && S_ISDIR(cur->stt->st_mode) &&
				(files = ft_eng_dir(cur, files, NULL, -1)))
			{
ft_pchar(chip + '0', 1);
ft_pnbr_base(__LINE__, 10, 1);
ft_pendl(__FUNCTION__, 1);
ft_pendl("", 1);
				ft_eng_launch(files, 1, files, NULL);
			}
			l = &(cur->next);
			free(cur->stt);
			free(cur->arg);
			free(cur);
			cur = NULL;
		}
	}
	if (l && *l)
		free(l);
	l = NULL;
	return (1);
}

char			ft_eng_parse_files(t_arg **cur, t_arg *tmp, char chip,
									t_arg **files)
{
	if (*cur)
	{
		chip = ((*cur)->err == ENOTDIR) ? 1 : 0;
		if (chip)
		{
			(*files) = (*cur);
			(*files)->next = NULL;
			cur = &tmp;
		}
		if (tmp)
			chip = (files && *files) ?
				ft_eng_parse_files(&tmp, tmp->next, 0, &(*files)->next)
				: ft_eng_parse_files(&tmp, tmp->next, 0, files);
	}
	return (0);
}

t_arg**		ft_eng_dir(const t_arg *cur, t_arg **l, DIR *d, ssize_t s)
{
	struct dirent	*dent;
	char			*c_buf;

	c_buf = NULL;
	if (!d && ((ft_strcmp(cur->arg, ".") && ft_strcmp(cur->arg, "..")) || s < 0))
	{
		d = opendir(cur->arg);
		if (ft_pstr(cur->arg, 1) && ft_pendl(":", 1) && (l = malloc(sizeof(t_arg*))))
			l = ft_eng_dir(cur, l, d, 0);
		closedir(d);
		if (ft_parse_sgl(-1) & CHAR_L && ft_pstr("total ", 1) &&
			ft_pnbr_base((long)s, 10, 1) && ft_pendl("", 1))
			d = NULL;
		ft_arg_time((const t_arg **)l, *l, *l);
	}
	else if ((l) && !(*l) && d && (dent = readdir(d)))
	{
		c_buf = ft_strdir((const char*)cur->arg, (const char*)dent->d_name);
		*l = ft_arg_node(c_buf, (const char*)dent->d_name, NULL);
		free(c_buf);
		(*l)->next = *ft_eng_dir(cur, &(*l)->next, d, s + ((*l)->stt->st_blocks));
	}
	else if (ft_parse_sgl(-1) & CHAR_L && ft_pstr("total ", 1) &&
			ft_pnbr_base((long)s, 10, 1))
		ft_pendl("", 1);
	return (l);
}
