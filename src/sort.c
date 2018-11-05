/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/01 17:10:55 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	sort_names(void *a, void *b)
{
	return (ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name));
}

int	sort_toend(void *a, void *b)
{
	a = a;
	b = b;
	return (-1);
}

int	sort(void *a, void *b)
{
	if (ISFLAG_F(g_flags))
		return (0);
	else
		return ((ISFLAG_R(g_flags)) ?
			-ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name) :
			ft_strcmp(((t_path *)a)->name, ((t_path *)b)->name));
}
