/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:13:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 14:44:53 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	perror_report(const char *str)
{
	char	*s;
	char	*msg;

	if (str)
		s = ft_strjoin(PROGRAM_NAME, ": ");
	else
		s = ft_strnew(0);
	msg = ft_strjoin(s, str);
	if (!(s && msg))
		perror_exit("");
	perror(msg);
	free((void *)(s));
	free((void *)(msg));
}

void	perror_exit(const char *str)
{
	char *s;

	if (*str)
	{
		s = ft_strjoin(PROGRAM_NAME, ": ");
		perror(ft_strjoin(s, str));
	}
	else
		perror(PROGRAM_NAME);
	exit(1);
}

void	error_option(char opt)
{
	char	*flags;

	flags = ft_strdup(FLAGS);
	ft_strsort(flags);
	ft_dprintf(STDERR,
		"%s: illegal option -- %c\nusage: ls [-%s] [file ...]\n",
		PROGRAM_NAME, opt, flags);
	free((void *)flags);
	exit(1);
}
