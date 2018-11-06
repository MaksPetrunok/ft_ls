/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/05 20:52:46 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		max_len(t_list *lst)
{
	int	len;
	int	cl;

	len = 0;
	while (lst)
	{
		cl = ft_strlen(VP(lst->content)->name);
		len = (cl > len) ? cl : len;
		lst = lst->next;
	}
	return (len);
}

void	print_table(t_list	*lst)
{
	struct winsize	ws;
	int				col;
	int				width;
	int				i;

//	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		perror_exit();
	col = ws.ws_col / (max_len(lst) + 2);
	width = ws.ws_col / col;

	i = 1;
	while (lst)
	{
		if (i % col == 0)
			i = ft_printf("\n");
		ft_printf("%-*s", width, VP(lst->content)->name);
		i++;
		lst = lst->next;
	}
	ft_printf("\n");
}

void	list_files(t_list *lst)
{
	if (lst == 0)
		return ;
	if (ISFLAG_L(g_flags))
	while (lst)
	{
		if (ISFLAG_I(g_flags))
			ft_printf("%d %s\n", VP(lst->content)->ino, VP(lst->content)->name);
		else
		{
			ft_printf("%s", VP(lst->content)->path);
			VP(lst->content)->pstat == 0 ? ft_printf("\n") :
				 ft_printf("%mode_dir: %#o\n", VP(lst->content)->pstat->st_mode);
		lst = lst->next;
		}
	}
	else
		print_table(lst);
}
