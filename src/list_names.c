/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 16:27:53 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*tlstdup(t_list *elem)
{
	t_list		*lst;
	t_path		*path;
	struct stat	*buff;

	lst = malloc(sizeof(t_list));
	path = malloc(sizeof(t_path));
	if (!(lst && path))
		perror_exit("");
	if (VP(elem->content)->pstat == 0)
		buff = 0;
	else
	{
		if ((buff = malloc(sizeof(struct stat))) == 0)
			perror_exit("");
		ft_memcpy(buff, (VP(elem->content)->pstat), sizeof(struct stat));
	}
	path->name = ft_strdup(VP(elem->content)->name);
	path->path = ft_strdup(VP(elem->content)->path);
	path->ino = VP(elem->content)->ino;
	path->pstat = buff;
	path->xat_acl = 0;
	lst->content = (void *)path;
	lst->next = 0;
	lst->content_size = elem->content_size;
	return (lst);
}

static void		init_path(t_path *p, char *name, char *npath, int ino)
{
	p->name = ft_strdup(name);
	p->path = npath;
	p->ino = ino;
	p->pstat = 0;
	p->xat_acl = 0;
}

static t_list	*pathtolist(char *name, char *npath, int ino, t_list **names)
{
	t_list		*elem;
	t_path		path;

	init_path(&path, name, npath, ino);
	if (IS_STAT_REQ(g_flags))
	{
		if ((path.pstat = (struct stat *)malloc(sizeof(struct stat))) == 0)
			perror_exit("");
		if (ISFLAG_LL(g_flags) ? stat(path.path, path.pstat) == -1 :
			lstat(path.path, path.pstat) == -1)
		{
			path.ino = 0;
			perror_report(name);
		}
	}
	if ((elem = ft_lstnew((void *)&path, sizeof(t_path))) == 0)
		perror_exit("");
	ft_lstins(names, elem, &sort);
	if (ISFLAG_RR(g_flags) && ISDIR(path.pstat->st_mode) &&
		ft_strcmp("..", name) != 0 && ft_strcmp(".", name) != 0)
		return (tlstdup(elem));
	return (0);
}

static void		iter_over_dir(DIR *dstr, t_list **names, t_list **subdirs,
		t_list *lst)
{
	struct dirent	*dirp;
	t_list			*tmp;

	*names = 0;
	*subdirs = 0;
	while ((dirp = readdir(dstr)) != 0)
	{
		if (*(dirp->d_name) == '.' && !ISFLAG_A(g_flags))
			continue ;
		tmp = pathtolist(dirp->d_name,
		add_parent(dirp->d_name, VP(lst->content)->path), dirp->d_ino, names);
		if (ISFLAG_RR(g_flags) && tmp)
			ft_lstins(subdirs, tmp, &sort);
		errno = 0;
	}
	if (errno != 0 && dirp == 0)
		perror_report(VP(lst->content)->name);
}

void			list_dir(t_list *lst)
{
	DIR				*dstr;
	t_list			*names;
	t_list			*subdirs;

	errno = 0;
	if ((dstr = opendir(*(VP(lst->content)->path) ?
				VP(lst->content)->path : VP(lst->content)->name)) == 0)
	{
		perror_report(VP(lst->content)->path);
		return ;
	}
	iter_over_dir(dstr, &names, &subdirs, lst);
	closedir(dstr);
	list_files(names, 1);
	ft_lstdel(&names, &free_path);
	write(1, "\n", subdirs != 0);
	iter_dirs(subdirs, 1);
	ft_lstdel(&subdirs, &free_path);
}
