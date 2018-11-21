/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 15:33:44 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_atime(void *a, void *b)
{
	struct timespec	ta;
	struct timespec	tb;

	ta = VP(a)->pstat->st_atimespec;
	tb = VP(b)->pstat->st_atimespec;
	if (ta.tv_sec != tb.tv_sec)
		return (ta.tv_sec < tb.tv_sec);
	else if (ta.tv_nsec != tb.tv_nsec)
		return (ta.tv_nsec < tb.tv_nsec);
	else
		return (ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name));
}

static int	sort_mtime(void *a, void *b)
{
	struct timespec	ta;
	struct timespec	tb;

	ta = VP(a)->pstat->st_mtimespec;
	tb = VP(b)->pstat->st_mtimespec;
	if (ta.tv_sec != tb.tv_sec)
		return (ta.tv_sec < tb.tv_sec);
	else if (ta.tv_nsec != tb.tv_nsec)
		return (ta.tv_nsec < tb.tv_nsec);
	else
		return (ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name));
}

static int	sort_size(void *a, void *b)
{
	off_t	sa;
	off_t	sb;

	sa = VP(a)->pstat->st_size;
	sb = VP(b)->pstat->st_size;
	if (sa != sb)
		return (sa < sb);
	else
		return (ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name));
}

int			sort(void *a, void *b)
{
	int	res;

	if (ISFLAG_F(g_flags))
		res = 0;
	else if (ISFLAG_SS(g_flags))
		res = sort_size(a, b);
	else if (ISFLAG_U(g_flags))
		res = sort_atime(a, b);
	else if (ISFLAG_T(g_flags))
		res = sort_mtime(a, b);
	else
		res = ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name);
	if (ISFLAG_R(g_flags))
		res = (res > 0) ? -1 : 1;
	return (res);
}
