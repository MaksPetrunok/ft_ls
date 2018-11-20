/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/20 19:01:25 by mpetruno         ###   ########.fr       */
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

char	*get_size(struct stat *st, char *buff)
{
	char	*ptr;
	if (ISCHR(st->st_mode) || ISBLK(st->st_mode))
	{
		ft_ulltoa_base(st->st_rdev >> 24 & 0xFFF, 10, 0, buff);
		ptr = buff + ft_strlen(buff);
		*ptr++ = ',';
		*ptr++ = ' ';
		ft_ulltoa_base(st->st_rdev & 0xFFFFF, 10, 0, ptr);
	}
	else
		ft_ulltoa_base(st->st_size, 10, 0, buff);
	return (buff);
}

int		get_sizelen(struct stat *st)
{
	int	len;

	if (ISCHR(st->st_mode) || ISBLK(st->st_mode))
		len = ft_numlen(st->st_rdev & 0xFFFFF) +
				ft_numlen((st->st_rdev >> 24) & 0xFFF) + 2;
	else
		len = ft_numlen(st->st_size);
	return (len);
}

static void    set_xattr_acl(t_path *path)
{
	acl_t		acl;
	acl_entry_t	acl_ent;
	ssize_t		xattr;

	if (path->ino == 0)
	{
		path->xat_acl = ' ';
		return ;
	}
#ifndef ON_LINUX
	acl = acl_get_link_np(path->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_ent) == -1)
	{
		acl_free(acl);
		acl = 0;
	}
#endif

#ifdef ON_LINUX
	if ((xattr = ISFLAG_LL(g_flags) ?
		listxattr(path->path, 0, 0) : llistxattr(path->path, 0, 0)) < 0)
#else
	if ((xattr = listxattr(path->path, 0, 0, XATTR_NOFOLLOW)) < 0)
//					ISFLAG_LL(g_flags))) < 0)
#endif
		xattr = 0;
	if (xattr > 0)
		path->xat_acl = '@';
	else if (acl != 0)
		path->xat_acl = '+';
	else
		path->xat_acl = ' ';
	acl_free(acl);
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
		tmp = ft_strlen(get_owner(st->st_uid)) + 1;
		fmt->own_len = (tmp > fmt->own_len) ? tmp : fmt->own_len;
		tmp = ft_strlen(get_group(st->st_gid)) + 1;
		fmt->grp_len = (tmp > fmt->grp_len) ? tmp : fmt->grp_len;
		tmp = get_sizelen(st); //ft_numlen(get_size(st));
		fmt->size_len = (tmp > fmt->size_len) ? tmp : fmt->size_len;
		set_xattr_acl(VP(lst->content));
		lst = lst->next;
	}
}
