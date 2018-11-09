/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 19:02:34 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// clarify priority of -t, -f, etc.. or no flag
static int	sort_mtime(void *a, void *b)
{
	struct timespec	ta;
	struct timespec	tb;
// 	UNIX:
	ta = VP(a)->pstat->st_mtimespec;
	tb = VP(b)->pstat->st_mtimespec;
//	LINUX:
//	ta = VP(a)->pstat->st_mtim;
//	tb = VP(b)->pstat->st_mtim;
	if (ta.tv_sec != tb.tv_sec)
		return (ta.tv_sec < tb.tv_sec);
	else if (ta.tv_nsec != tb.tv_nsec)
		return (ta.tv_nsec < tb.tv_nsec);
	else
		return (ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name));
}

int			sort(void *a, void *b)
{
	int	res;

	if (ISFLAG_F(g_flags))
		res = 0;
	else if (ISFLAG_T(g_flags))
		res = sort_mtime(a, b);
	else
		res = ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name);
	if (ISFLAG_R(g_flags))
		res = -res;
	return (res);
}
