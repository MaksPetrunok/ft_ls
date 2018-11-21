/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_det_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 16:42:11 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_name(t_path *path, char *buff)
{
	int			size;
	struct stat	st;

	if (ISFLAG_GG(g_flags))
		set_color(path->ino == 0 ? 1 : path->pstat->st_mode);
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
		write(1, "\n", 1);
	}
	else
		ft_printf("%s\n", path->name);
	if (ISFLAG_GG(g_flags))
		set_color(0);
}

static void	print_missing_lnk(t_dout *fmt)
{
	if (ISFLAG_I(g_flags))
		ft_printf("%*c ", fmt->ino_len, '?');
	if (ISFLAG_G(g_flags))
		ft_printf("l?????????  %*s%*c %*-c %*c %*c ",
			fmt->xat_acl, "",
			fmt->lnk_len, '?',
			fmt->grp_len, '?',
			fmt->size_len, '?',
			12, '?');
	else
		ft_printf("l?????????  %*s%*c %*-c %*-c %*c %*c ",
			fmt->xat_acl, "",
			fmt->lnk_len, '?',
			fmt->own_len, '?',
			fmt->grp_len, '?',
			fmt->size_len, '?',
			12, '?');
}

static char	*get_time(struct stat *st, char *buff)
{
	time_t	now;
	time_t	diff;
	char	*tmp;
	time_t	half_year;

	half_year = 15778463;
	tmp = ctime(&(st->st_mtimespec.tv_sec)) + 4;
	diff = time(&now) - st->st_mtimespec.tv_sec;
	if (diff > half_year || diff < -half_year)
	{
		ft_strncpy(buff, tmp, 6);
		buff[6] = ' ';
		buff[7] = ' ';
		tmp += 15;
		while (*tmp == ' ')
			tmp++;
		ft_strncpy(buff + 8, tmp, ft_strlen(tmp) - 1);
		buff[7 + ft_strlen(tmp)] = 0;
	}
	else
	{
		ft_strncpy(buff, tmp, 12);
		buff[12] = 0;
	}
	return (buff);
}

static void	print_details(struct stat *st, char *acc, t_dout *fmt)
{
	char	buff[20];
	char	t[30];

	if (ISFLAG_I(g_flags))
		ft_printf("%*d ", fmt->ino_len, st->st_ino);
	if (ISFLAG_G(g_flags))
		ft_printf("%c%*-s%*d %*-s %*s %s ",
			get_type(st->st_mode),
			(9 + fmt->xat_acl), acc,
			fmt->lnk_len, st->st_nlink,
			fmt->grp_len, get_group(st->st_gid),
			fmt->size_len, get_size(st, buff),
			get_time(st, t));
	else
		ft_printf("%c%*-s%*d %*-s %*-s %*s %s ",
			get_type(st->st_mode),
			11, acc,
			fmt->lnk_len, st->st_nlink,
			fmt->own_len, get_owner(st->st_uid),
			fmt->grp_len, get_group(st->st_gid),
			fmt->size_len, get_size(st, buff),
			get_time(st, t));
}

void		print_det_lst(t_list *lst, int total)
{
	t_dout		fmt;
	struct stat	*st;
	char		acc[12];
	char		buff[PATH_BUFF_SIZE];

	fill_fmt(&fmt, lst);
	if (total)
		ft_printf("total %ld\n", fmt.total);
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
		print_name(VP(lst->content), buff);
		lst = lst->next;
	}
}
