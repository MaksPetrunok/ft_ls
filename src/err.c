/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:13:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/01 16:15:17 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	perror_exit(void)
{
if (errno = ENOENT)
ft_printf("error here\n");
	perror(PROGRAM_NAME);
	exit(1);
}

void	error_option(char opt)
{
	ft_dprintf(2,
		"%s: illegal option -- %c\nusage: ls [-%s] [file ...]\n",
		PROGRAM_NAME, opt, FLAGS);
	exit(1);
}
