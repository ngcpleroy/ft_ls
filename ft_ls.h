/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleroy <nleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:15:23 by nleroy            #+#    #+#             */
/*   Updated: 2015/02/11 16:46:15 by nleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <fcntl.h>
# include <stdlib.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>

#  define CHAR_A 1
#  define CHAR_L 2
#  define CHAR_R 4
#  define CHAR_RR 8
#  define CHAR_T 16

#  define XATTRSIZE 10000

#  define N XATTR_NOFOLLOW

#  define A ACL_TYPE_ACCESS

typedef struct	s_arg
{
	struct s_arg	*next;
	struct stat		*stt;
	char			*arg;
	char			*lg;
	int				err;
}				t_arg;

struct t
{ 
	char	c;
	int		flag;
};

struct tt
{ 
	char	c;
	int		f1;
	int		f2;
	int		f3;
};

/*
** ft_parse.c
*/

char			ft_parse_option(const char **av, const unsigned int i, char r);
char			ft_parse_sgl(const char value);

/*
** ft_arg.c
*/

t_arg			*ft_arg_list(const char **av, const size_t s, t_arg *cr_arg);
void			ft_arg_alpha(const t_arg **begin, t_arg *tmp, t_arg *t);
void			ft_arg_time(const t_arg **begin, t_arg *tmp, t_arg *t);
void			ft_arg_revolve(t_arg **begin, t_arg *save, t_arg *head);
char			ft_arg_dump_errors(t_arg **cur, t_arg *tmp, char chip);

/*
** ft_eng.c
*/

char			ft_eng_launch(t_arg **list, char chip, t_arg **files, 
								t_arg *cur);
char			ft_eng_parse_files(t_arg **cur, t_arg *tmp, char chip,
								t_arg **files);
t_arg**			ft_eng_dir(const t_arg *cur, t_arg **list, DIR *dir, 
							ssize_t size);
char			ft_eng_file(const t_arg *l, ssize_t k, char c, char *a);
unsigned char	ft_eng_blks(const t_arg *cur, const char k, int c,
							unsigned char r);


/*
** ft_tools1.c
*/

char			*ft_strdup(const char *src);
size_t			ft_strlen(const char *str);
unsigned int	ft_nbrlen(const long l);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdir(const char *s1, const char *s2);

/*
** ft_tools2.c
*/

char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *s1, char const *s2);
void			*ft_memmove(void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);

/*
** ft_tools3.c
*/

void			*ft_sizetab(int *tab, int s);
int				ft_atoi(char *str);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
char			*ft_strsub(const char *s1, unsigned int start, size_t len);
void			ft_bzero(void *s, size_t n);

/*
** ft_put
*/

char	ft_pchar(const char c, const int fd);
char	ft_pstr(const char *c, const int fd);
char	ft_pstr2(const char *c, const int fd, size_t s, const size_t e);
char	ft_pendl(const char *c, const int fd);
char	ft_pnbr_base(const long n, const int base, const int fd);

#endif
