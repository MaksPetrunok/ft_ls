/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 21:12:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/20 21:40:11 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#define ON_LINUX

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "colors.h"

# include <sys/xattr.h> // added for xattr
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/acl.h>

# define PROGRAM_NAME "ft_ls"
//# define FLAGS	"alrRtdfimL1xCugS"
# define FLAGS		"ftuSRLlgmxC1ardiG"

/* Flags passed to the program. Single character represents small letter,
 * double characters represent capital letter (r -> R, R -> RR). */
# define F_F	0x0001
# define F_T	0x0002
# define F_U	0x0004
# define F_SS	0x0008
# define F_RR	0x0010
# define F_LL	0x0020
# define F_L	0x0040
# define F_G	0x0080
# define F_M	0x0100
# define F_X	0x0200
# define F_CC	0x0400
# define F_1	0x0800
# define F_A	0x1000
# define F_R	0x2000
# define F_D	0x4000
# define F_I	0x8000
# define F_GG	0x10000

# define F_ST	0x100FE

# define ISFLAG_A(X) (F_A & X)
# define ISFLAG_L(X) (F_L & X)
# define ISFLAG_R(X) (F_R & X)
# define ISFLAG_RR(X) (F_RR & X)
# define ISFLAG_T(X) (F_T & X)
# define ISFLAG_D(X) (F_D & X)
# define ISFLAG_F(X) (F_F & X)
# define ISFLAG_I(X) (F_I & X)
# define ISFLAG_M(X) (F_M & X)
# define ISFLAG_LL(X) (F_LL & X)
# define ISFLAG_1(X) (F_1 & X)
# define ISFLAG_X(X) (F_X & X)
# define ISFLAG_CC(X) (F_CC & X)
# define ISFLAG_U(X) (F_U & X)
# define ISFLAG_G(X) (F_G & X)
# define ISFLAG_SS(X) (F_SS & X)
# define ISFLAG_GG(X) (F_GG & X)
# define IS_STAT_REQ(X) (F_ST & X)

# define ISFIFO(X) ((S_IFMT & X) == S_IFIFO)
# define ISCHR(X) ((S_IFMT & X) == S_IFCHR)
# define ISDIR(X) ((S_IFMT & X) == S_IFDIR)
# define ISBLK(X) ((S_IFMT & X) == S_IFBLK)
# define ISREG(X) ((S_IFMT & X) == S_IFREG)
# define ISLNK(X) ((S_IFMT & X) == S_IFLNK)
# define ISSOCK(X) ((S_IFMT & X) == S_IFSOCK)
# define ISWHT(X) ((S_IFMT & X) == S_IFWHT)

# define VP(X) ((t_path *)(X))	/* convert (void *) to (t_path *) */

# define PATH_BUFF_SIZE 4096 /* buffer size for storing path reffered by soft link */
# define COL_OFFSET	2	/* minimum number of spaces between output columns */
# define STDIN	0
# define STDOUT 1
# define STDERR 2

# define PERM_R 'r'
# define PERM_W 'w'
# define PERM_X 'x'
# define PERM_N '-'

extern unsigned long int	g_flags;

typedef struct	s_path
{
	const char	*name;
	const char	*path;
	int			ino;
	struct stat	*pstat;
	char		xat_acl;
}				t_path;

typedef struct	s_out
{
	t_path		*path;
	short		name_len;	/* minimum length of string for name */
	short		ino_len;	/* minimum number of digits for inode */
}				t_out;

// fill this structure with data and use for formatting strin
typedef struct	s_dout
{
	long		total;		/* number of blocks */
	short		ino_len;	/* minimum number of digits for inode */
	short		lnk_len;	/* minimum num. of digits in num. of links */
	short		own_len;	/* etc.. */
	short		grp_len;
	short		size_len;
	short		date_len;
	short		time_len;
	short		xat_acl;
}				t_dout;

void	set_color(mode_t mode);

char	get_type(mode_t mode);
char	*get_size(struct stat *st, char *buff);
char	*get_owner(uid_t uid);
char	*get_group(gid_t gid);
void	get_acc(char *buff, t_path *path);

void	init_fmt(t_dout *fmt);
void	fill_fmt(t_dout *fmt, t_list *lst);

void	free_path(void *content, size_t size);
void	free_arr(t_out **arr);

void	iter_dirs(t_list *dirs, int print_dir_name);
void	process_input(t_list *files, t_list *dirs, int print_dir);
void	list_files(t_list *lst, int total);
void	list_dir(t_list *lst);

void    perror_exit(const char *s);
void    perror_report(const char *s);
void	error_option(char c);

int		sort(void *a, void *b);
t_out	**list_to_arr(t_list *lst, int *max_ino, int *max_name);

void	get_path(char *name, t_path *buff);
void	print_paths(t_list *lst, int printdirname);
void	print_table(t_list *lst);
void	print_tablex(t_list *lst);
void	print_det_lst(t_list *lst, int total);

#endif
