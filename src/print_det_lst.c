/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_det_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 21:32:09 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void print_name(t_path *path, char *buff)
{
	int			size;
	struct stat	st;

	if (ISLNK(path->pstat->st_mode))
	{
		if ((size = readlink(path->path, buff, PATH_BUFF_SIZE)) == -1)
			perror_report("");
		else
			buff[size] = '\0';
		errno = 0;
		stat(path->path, &st);
		ft_putstr(path->name);
		ft_putstr(" -> ");
		if (errno == ENOENT && ISFLAG_GG(g_flags))
			set_color(1);
		ft_putstr(buff);		
		set_color(0);
		write(1, "\n", 1);
	}
	else
		ft_printf("%s\n", path->name);
}

static void	print_missing_lnk(t_dout *fmt)
{
	if (ISFLAG_I(g_flags))
		ft_printf("%*c ", fmt->ino_len, '?');
	if (ISFLAG_G(g_flags))
		ft_printf("l?????????%*s%*c %*-c %*c %*c ",
			fmt->xat_acl, "",
			fmt->lnk_len, '?',
			fmt->grp_len, '?',
			fmt->size_len, '?',
			12, '?');
	else
		ft_printf("l?????????%*s%*c %*-c %*-c %*c %*c ",
			fmt->xat_acl, "",
			fmt->lnk_len, '?',
			fmt->own_len, '?',
			fmt->grp_len, '?',
			fmt->size_len, '?',
			12, '?');
}

static void	print_details(struct stat *st, char *acc, t_dout *fmt)
{
	char	buff[20];

	if (ISFLAG_I(g_flags))
		ft_printf("%*d ", fmt->ino_len, st->st_ino);
	if (ISFLAG_G(g_flags))
		ft_printf("%c%*-s%*d %*-s %*s %.*s ",
			get_type(st->st_mode),
			(9 + fmt->xat_acl), acc,
			fmt->lnk_len, st->st_nlink,
			fmt->grp_len, get_group(st->st_gid),
			//fmt->size_len, st->st_size, // for device files print {major, minor} numbers (st_dev)
			fmt->size_len, get_size(st, buff),
//ft_strlen(ctime(&(st->st_mtimespec.tv_sec)))-1, ctime(&(st->st_mtimespec.tv_sec)),
			12, ctime(&(st->st_mtim.tv_sec)) + 4);
	else
		ft_printf("%c%*-s%*d %*-s %*-s %*s %.*s ",
			get_type(st->st_mode),
			(9 + fmt->xat_acl), acc,
			fmt->lnk_len, st->st_nlink,
			fmt->own_len, get_owner(st->st_uid),
			fmt->grp_len, get_group(st->st_gid),
//			fmt->size_len, st->st_size,
			fmt->size_len, get_size(st, buff),
//ft_strlen(ctime(&(st->st_mtimespec.tv_sec)))-1, ctime(&(st->st_mtimespec.tv_sec)),
			12, ctime(&(st->st_mtim.tv_sec)) + 4);
}

void		print_det_lst(t_list *lst)
{
	t_dout		fmt;
	struct stat	*st;
	char		acc[12];
	char		buff[PATH_BUFF_SIZE];

	fill_fmt(&fmt, lst);
//ft_printf("xattr_acc=%d\n", fmt.xat_acl);
	ft_printf("total: %ld\n", fmt.total);
	while (lst)
	{
		if (ISFLAG_LL(g_flags) && VP(lst->content)->ino == 0)
			print_missing_lnk(&fmt);
		else
		{
			st = VP(lst->content)->pstat;
			get_acc(acc, VP(lst->content));
			print_details(st, acc, &fmt);
		}
		if (ISFLAG_GG(g_flags))
			set_color(VP(lst->content)->ino == 0 ? 1 : VP(lst->content)->pstat->st_mode);
		print_name(VP(lst->content), buff);
		if (ISFLAG_GG(g_flags))
			set_color(0);
		lst = lst->next;
	}
}
