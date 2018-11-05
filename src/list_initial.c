/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_initial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/01 17:10:55 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_initial(t_list *files, t_list *dirs)
{
	int	print_dir_name;
	int	size;

	size = ft_lstsize(dirs);
	print_dir_name = size > 1 || (files && dirs);
	list_files(files);
	if (files && dirs)
		write(1, "\n", 1);
	ft_lstdel(&files, &free_path);
	while (dirs)
	{
		if (print_dir_name)
			ft_printf("%s:\n", VP(dirs->content)->name);
		list_dir(dirs);
		if (size-- > 1)
			write(1, "\n", 1);
		dirs = dirs->next;
	}
}
