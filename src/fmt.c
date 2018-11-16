/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 21:32:09 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_fmt(t_dout *fmt)
{
	fmt->total = 0;
	fmt->ino_len = 0;
	fmt->lnk_len = 0;
	fmt->own_len = 0;
	fmt->grp_len = 0;
	fmt->size_len = 0;
	fmt->date_len = 0;
	fmt->time_len = 0;
	fmt->xat_acl = 0;
}

static short    has_xattr(t_path *path)
{
	int	res;

	if (path->ino == 0)
		return (0);
// IS LINUX?
#ifdef ON_LINUX
	if ((res = ISFLAG_LL(g_flags) ?
		listxattr(path->path, 0, 0) : llistxattr(path->path, 0, 0)) < 0)
#else
	if ((res = listxattr(path->path, 0, 0, ISFLAG_LL(g_flags))) < 0)
#endif
	{
		perror_report(path->path);
		return (0);
	}
	path->xat_acl = (res > 0);
	return (res > 0);
}

void	fill_fmt(t_dout *fmt, t_list *lst)
{
	int			tmp;
	struct stat	*st;

	init_fmt(fmt);
	while (lst)
	{
		st = VP(lst->content)->pstat;
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
		fmt->xat_acl |= (has_xattr(VP(lst->content))); // and here get_acl()
		lst = lst->next;
	}
	fmt->xat_acl = (fmt->xat_acl >= 2) ? fmt->xat_acl : fmt->xat_acl + 1;
}
