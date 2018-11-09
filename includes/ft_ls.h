/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 21:12:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 21:15:45 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
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

# define PROGRAM_NAME "ft_ls"
# define FLAGS	"alrRtdfimL1xC"

/* flags passed to the program */
// REPLACE bit offset with numbers
# define F_A	1U << 0 
# define F_L	1U << 1
# define F_R	1U << 2
# define F_RR	1U << 3
# define F_T	1U << 4
# define F_D	1U << 5
# define F_F	1U << 6
# define F_I	1U << 7
# define F_M	1U << 8
# define F_LL	1U << 9
# define F_1	1U << 10
# define F_X	1U << 11
# define F_CC	1U << 12

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

# define ISFIFO(X) ((S_IFMT & X) == S_IFIFO)
# define ISCHR(X) ((S_IFMT & X) == S_IFCHR)
# define ISDIR(X) ((S_IFMT & X) == S_IFDIR)
# define ISBLK(X) ((S_IFMT & X) == S_IFBLK)
# define ISREG(X) ((S_IFMT & X) == S_IFREG)
# define ISLNK(X) ((S_IFMT & X) == S_IFLNK)
# define ISSOCK(X) ((S_IFMT & X) == S_IFSOCK)
# define ISWHT(X) ((S_IFMT & X) == S_IFWHT)

# define VP(X) ((t_path *)(X))	/* convert (void *) to (t_path *) */

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
}				t_dout;

void	free_path(void *content, size_t size);
void	free_arr(t_out **arr);

void	iter_dirs(t_list *dirs, int print_dir_name);
void	process_input(t_list *files, t_list *dirs);
void	list_files(t_list *lst);
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

#endif
