/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:22:47 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 15:23:09 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_path
{
	const char	*name;
	const char	*path;
	int			ino;
	struct stat	*pstat;
	char		xat_acl;
}				t_path;

typedef struct	s_out
{
	t_path		*path;
	short		name_len;
	short		ino_len;
}				t_out;

typedef struct	s_dout
{
	long		total;
	short		ino_len;
	short		lnk_len;
	short		own_len;
	short		grp_len;
	short		size_len;
	short		date_len;
	short		time_len;
	short		xat_acl;
}				t_dout;

#endif
