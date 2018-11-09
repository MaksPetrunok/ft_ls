/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 21:32:09 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
The <entry type> character shall describe the type of file, as follows:
d Directory.
b Block special file.
c Character special file.
l(ell) Symbolic link.
p FIFO.
- Regular file.

If the -l option is specified without -L, the following information
shall be written:

"%s %u %s %s %u %s %s\n", <file mode>, <number of links>,
    <owner name>, <group name>, <number of bytes in the file>,
    <date and time>, <pathname>

*/

static void	init_fmt(t_dout *fmt)
{
	fmt->total = 0;
	fmt->ino_len = 0;
	fmt->lnk_len = 0;
	fmt->own_len = 0;
	fmt->grp_len = 0;
	fmt->size_len = 0;
	fmt->date_len = 0;
	fmt->time_len = 0;
}

char		get_type(mode_t mode)
{
	if (ISDIR(mode))
		return ('d');
	else if (ISREG(mode))
		return ('-');
	else if (ISLNK(mode))
		return ('l');
	else if (ISCHR(mode))
		return ('c');
	else if (ISBLK(mode))
		return ('b');
	else if (ISFIFO(mode))
		return ('p');
	return ('?');
}

char	*get_owner(uid_t uid)
{
	struct passwd	*tmp;

	tmp = getpwuid(uid);
	return (tmp->pw_name);
}

char	*get_group(gid_t gid)
{
	struct group	*tmp;

	tmp = getgrgid(gid);
	return (tmp->gr_name);
}

static void	fill_fmt(t_dout *fmt, struct stat *st)
{
	int	tmp;
	fmt->total += st->st_blocks;
	if (ISFLAG_I(g_flags))
	{
		tmp = ft_numlen(st->st_ino);
		fmt->ino_len = (tmp > fmt->ino_len) ? tmp : fmt->ino_len;
	}
	tmp = ft_numlen(st->st_nlink);
	fmt->lnk_len = (tmp > fmt->lnk_len) ? tmp : fmt->lnk_len;
	tmp = ft_strlen(get_owner(st->st_uid));
	fmt->own_len = (tmp > fmt->own_len) ? tmp : fmt->own_len;
	tmp = ft_strlen(get_group(st->st_gid));
	fmt->grp_len = (tmp > fmt->grp_len) ? tmp : fmt->grp_len;
	
	tmp = ft_numlen(st->st_size);
	fmt->size_len = (tmp > fmt->size_len) ? tmp : fmt->size_len;

}

static void	get_acc(char *buff, mode_t mode)
{
	short	i;

	i = 8;
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_X : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_X : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_X : PERM_N;
	*buff = '\0';
}

static void	print_details(t_list *lst)
{
	t_dout		fmt;
	t_list		*tmp;
	struct stat	*st;
	char		acc[10];

	init_fmt(&fmt);
	tmp = lst;
	while (tmp)
	{
		fill_fmt(&fmt, VP(tmp->content)->pstat);
		tmp = tmp->next;
	}
	ft_printf("total: %ld\n", fmt.total);
	while (lst)
	{
		st = VP(lst->content)->pstat;
		get_acc(acc, st->st_mode);
		if (ISFLAG_I(g_flags))
			ft_printf("%*d ", fmt.ino_len, VP(lst->content)->pstat->st_ino);
		ft_printf("%c%s %*d %*-s %*-s %*d %.*s %s\n",
				get_type(st->st_mode),
				acc,
				fmt.lnk_len, st->st_nlink,
				fmt.own_len, get_owner(st->st_uid),
				fmt.grp_len, get_group(st->st_gid),
				fmt.size_len, st->st_size,
ft_strlen(ctime(&(st->st_mtimespec.tv_sec)))-1, ctime(&(st->st_mtimespec.tv_sec)),
				VP(lst->content)->name);
		lst = lst->next;
	}
}

void	list_files(t_list *lst)
{
//ft_printf("sizeof(t_dout)=%lu\n", sizeof(t_dout));
//ft_printf("sizeof(t_out)=%lu\n", sizeof(t_out));

	if (lst == 0)
		return ;
	if (ISFLAG_L(g_flags))
		print_details(lst);
	else
		print_table(lst);
}
