/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 21:32:09 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_color(mode_t mode)
{
	if (mode == 0)
		ft_putstr(RESET);
	else if (ISDIR(mode))
		ft_putstr(BLUE_BD);
	else if (ISLNK(mode))
		ft_putstr(GREEN);
	else if (ISREG(mode))
		ft_putstr(DEFAULT);
	else if (ISCHR(mode))
		ft_putstr(YELLOW);
	else if (ISBLK(mode))
		ft_putstr(MAGENTA);
	else if (ISSOCK(mode))
		ft_putstr(CYAN);
	else
		ft_putstr(RED);
}
