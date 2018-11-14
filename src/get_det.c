/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_det.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 21:32:09 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_type(mode_t mode)
{
	if (ISDIR(mode))
		return ('d');
	else if (ISREG(mode))
		return ('-');
	else if (ISLNK(mode))
		return ('l');
	else if (ISCHR(mode))
		return ('c');
	else if (ISBLK(mode))
		return ('b');
	else if (ISFIFO(mode))
		return ('p');
	return ('?');
}

char	*get_owner(uid_t uid)
{
	struct passwd	*tmp;

	tmp = getpwuid(uid);
	return (tmp->pw_name);
}

char	*get_group(gid_t gid)
{
	struct group	*tmp;

	tmp = getgrgid(gid);
	return (tmp->gr_name);
}

void	get_acc(char *buff, mode_t mode)
{
	short	i;

	i = 8;
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_X : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_X : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_X : PERM_N;
	*buff = '\0';
}
