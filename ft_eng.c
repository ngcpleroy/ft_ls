/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eng.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/06 13:18:30 by nleroy            #+#    #+#             */
/*   Updated: 2015/03/09 14:23:35 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Engine bloc, running on arguments the different options.
*/

#include "ft_ls.h"

const struct ft_cpt g_ft_cpt[9] = 
{
	{0, ft_cpt_links},
	{1, ft_cpt_user},
	{2, ft_cpt_group},
	{3, ft_cpt_major},
	{4, ft_cpt_size},
	{5, ft_cpt_time},
	{6, ft_cpt_name},
	{7, ft_cpt_link}
}

const struct ft_pl g_ft_pl[9] = 
{
	{0, ft_pl_links},
	{1, ft_pl_user},
	{2, ft_pl_group},
	{3, ft_pl_major},
	{4, ft_pl_size},
	{5, ft_pl_time},
	{6, ft_pl_name},
	{7, ft_pl_link}
}

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

char			ft_eng_launch(t_arg **l, char chip, t_arg **files, t_arg *cur)
{
	if (l && *l)
	{
		if (!chip)
			chip = (!chip) ? ft_eng_parse_files(l, (*l)->next, 0, files) : 1;
		chip = (!chip && files) ? ft_eng_launch(files, 1, files, NULL) : chip;
		chip += (files) ? ft_eng_file_launch((const t_arg*) *l, 1) : 0;
		while (l && *l && (cur = (*l)))
		{
			cur = *l;
			if ((ft_parse_sgl(-1) & CHAR_RR || !chip) && S_ISDIR(cur->stt->st_mode) &&
				(files = ft_eng_dir(cur, files, NULL, -1)))
				ft_eng_launch(files, 1, files, NULL);
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

char	ft_eng_file_launch(const t_arg *cur, int i)
{
	int		ends[9];
	int		total_size;
	char	*str;

	str = NULL;
	ends[0] = 0;
	if (ft_parse_sgl(-1) & CHAR_L)
	{
		while (i < 9)
		{
			ends[i] = g_ft_cpt[i].ft(cur, 0);
			total_size += ends[i];
			i++;
		}
		if ((str = (char*)malloc(total_size + 8 + 10)))
			ft_format_fresh(&str, total_size + 8 + 10);
	}
	ft_eng_file_play(cur, ends, &str);
	if (str)
		free(str);
	return (i);
}

char	ft_eng_file_play(const t_arg *cur, int ends[8], char **str, char i)
{
	int		j;
	char	c;

	c = 0;
	if (cur && ft_parse_sgl(-1) & CHAR_L)
	{
		while ((j = 0) && c < 10 && cur && !cur->err)
		{
			while (i < 7 && !((cur->stt->st_mode & g_t[j].flag && c == 0)
			|| (!(cur->stt->st_mode & g_tt[j].f1) && c < 4)
			|| (!(cur->stt->st_mode & g_tt[j].f2) && c >= 4 && c < 7)
			|| (!(cur->stt->st_mode & g_tt[j].f3) && c >= 7 && c < 10)))
				i++;
			c += (c >= 0) ? ft_pchar(g_tt[j].c, 1) : ft_pchar(g_t[j].c, 1);
			c += (c == 10) ? ft_pchar(' ', 1) : 0;
		}
		while (8 < 8)
			i += g_ft_pl.ft(cur, *str), end[i + 1]);
		ft_format_fresh(str, ft_strlen(*str) + 1);
		return (ft_eng_file_play(cur->next, ends, str, 0));
	}
	else if (cur)
		ft_pendl(cur->lg, 1);
	return (1);
}
