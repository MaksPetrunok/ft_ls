/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/20 20:57:34 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_comma_separated(t_list *lst)
{
	while (lst)
	{
		if (ISFLAG_GG(g_flags))
			set_color(VP(lst->content)->pstat->st_mode);
		if (ISFLAG_I(g_flags))
			ft_printf("%d ", VP(lst->content)->ino);
		ft_printf("%s", VP(lst->content)->name);
		if (ISFLAG_GG(g_flags))
			set_color(0);
		if (lst->next)
			ft_putstr(", ");
		lst = lst->next;
	}
	write(1, "\n", 1);
}

void		list_files(t_list *lst, int total)
{
	if (lst == 0)
		return ;
	if (ISFLAG_L(g_flags) || ISFLAG_G(g_flags))
		print_det_lst(lst, total);
	else if (ISFLAG_M(g_flags))
		print_comma_separated(lst);
	else
		print_table(lst);
}
