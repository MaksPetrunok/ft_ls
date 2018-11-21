/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_initial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 15:26:28 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	process_input(t_list *files, t_list *dirs, int print_dir)
{
	int	print_dir_name;
	int	size;

	size = ft_lstsize(dirs);
	print_dir_name = print_dir > 1;
	list_files(files, 0);
	if (files && dirs)
		write(1, "\n", 1);
	ft_lstdel(&files, &free_path);
	iter_dirs(dirs, print_dir_name);
	ft_lstdel(&dirs, &free_path);
}

void	iter_dirs(t_list *dirs, int print_dir_name)
{
	int	size;

	size = ft_lstsize(dirs);
	while (dirs)
	{
		if (print_dir_name)
			ft_printf("%s:\n", VP(dirs->content)->path);
		list_dir(dirs);
		if (size-- > 1)
			write(1, "\n", 1);
		dirs = dirs->next;
	}
}
