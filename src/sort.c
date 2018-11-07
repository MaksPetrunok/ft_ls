/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/07 17:36:17 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_mtime(void *a, void *b)
{
	t_path	*tmp1;

	if (a || b)
		a = b;
	//see types.h for struct timespec definition
	return (-1);
}

int	sort(void *a, void *b)
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
