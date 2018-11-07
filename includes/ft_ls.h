/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 21:12:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/07 17:19:48 by mpetruno         ###   ########.fr       */
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

# define PROGRAM_NAME "ft_ls"
# define FLAGS	"alrRtdfimL1"

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
# define F_ONE	1U << 10

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
# define ISFLAG_1(X) (F_ONE & X)

# define ISFIFO(X) ((S_IFMT & X) == S_IFIFO)
# define ISCHR(X) ((S_IFMT & X) == S_IFCHR)
# define ISDIR(X) ((S_IFMT & X) == S_IFDIR)
# define ISBLK(X) ((S_IFMT & X) == S_IFBLK)
# define ISREG(X) ((S_IFMT & X) == S_IFREG)
# define ISLNK(X) ((S_IFMT & X) == S_IFLNK)
# define ISSOCK(X) ((S_IFMT & X) == S_IFSOCK)
# define ISWHT(X) ((S_IFMT & X) == S_IFWHT)
# define VP(X) ((t_path *)(X))

extern unsigned long int	g_flags;

typedef struct	s_path
{
	const char	*name;
	const char	*path;
	int			ino;
	struct stat	*pstat;
}				t_path;

void	free_path(void *content, size_t size);

void	iter_dirs(t_list *dirs, int print_dir_name);
void	process_input(t_list *files, t_list *dirs);
void	list_files(t_list *lst);
void	list_dir(t_list *lst);

void    perror_exit(const char *s);
void    perror_report(const char *s);
void	error_option(char c);

int		sort(void *a, void *b);

void	get_path(char *name, t_path *buff);
void	print_paths(t_list *lst, int printdirname);

#endif
