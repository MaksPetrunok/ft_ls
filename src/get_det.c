/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_det.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:52:09 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 15:34:22 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		get_type(mode_t mode)
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
	else if (ISSOCK(mode))
		return ('s');
	return ('?');
}

char		*get_owner(uid_t uid)
{
	struct passwd	*tmp;

	tmp = getpwuid(uid);
	return (tmp->pw_name);
}

char		*get_group(gid_t gid)
{
	struct group	*tmp;

	tmp = getgrgid(gid);
	return (tmp->gr_name);
}

static char	get_xp(mode_t mode, char loc, char is_exec)
{
	if (loc & 3)
	{
		if (!is_exec && (mode & ((loc & 1) ? S_ISUID : S_ISGID)))
			return ('S');
		else if (is_exec && (mode & ((loc & 1) ? S_ISUID : S_ISGID)))
			return ('s');
	}
	else if ((loc & 4) && (mode & S_ISVTX))
		return (is_exec ? 't' : 'T');
	return (is_exec ? 'x' : '-');
}

void		get_acc(char *buff, t_path *path)
{
	mode_t	mode;
	short	i;

	mode = path->pstat->st_mode;
	i = 8;
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = get_xp(mode, 1, (mode & (1 << i--)));
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = get_xp(mode, 2, (mode & (1 << i--)));
	*buff++ = (mode & (1 << i--)) ? PERM_R : PERM_N;
	*buff++ = (mode & (1 << i--)) ? PERM_W : PERM_N;
	*buff++ = get_xp(mode, 4, (mode & (1 << i--)));
	*buff++ = path->xat_acl;
	*buff++ = ' ';
	*buff = '\0';
}
