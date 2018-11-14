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

static void	print_comma_separated(t_list *lst)
{
	while (lst)
	{
		if (ISFLAG_I(g_flags))
			ft_printf("%d ", VP(lst->content)->ino);
		if (lst->next)
			ft_printf("%s, ", VP(lst->content)->name);
		else
			ft_printf("%s", VP(lst->content)->name);
		lst = lst->next;
	}
	write(1, "\n", 1);
}

void		list_files(t_list *lst)
{
	if (lst == 0)
		return ;
	if (ISFLAG_L(g_flags) || ISFLAG_G(g_flags))
		print_det_lst(lst);
	else if (ISFLAG_M(g_flags))
		print_comma_separated(lst);
	else
		print_table(lst);
}
