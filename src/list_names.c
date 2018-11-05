/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/05 21:38:56 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*add_parent(const char *name, const char *parent)
{
	char	*dir;
	char	*res;

	if ((dir = ft_strjoin(parent, "/")) == 0)
		perror_exit();
	if ((res = ft_strjoin(dir, name)) == 0)
		perror_exit();
	free((void *)dir);
	return (res);
}

static t_list *tlstdup(t_list *elem)
{
	t_list		*lst;
	t_path		*path;
	struct stat	*buff;

	lst = malloc(sizeof(t_list));
	path = malloc(sizeof(t_path));
	if (!(lst && path))
		perror_exit();
	if (VP(elem->content)->pstat == 0)
		buff = 0;
	else
	{
		if ((buff = malloc(sizeof(struct stat))) == 0)
			perror_exit();
		ft_memcpy(buff, (VP(elem->content)->pstat), sizeof(struct stat));
	}
	path->name = ft_strdup(VP(elem->content)->name);
	path->ino = VP(elem->content)->ino;
	path->pstat = buff;
	lst->content = (void *)path;
	lst->next = 0;
	lst->content_size = elem->content_size;
	return (lst);
}

static t_list	*pathtolist(char *name, int ino, t_list **names)
{
	t_list		*elem;
	t_path		*path;

	elem = malloc(sizeof(t_list));
	path = malloc(sizeof(t_path));
	if (!(path && elem))
		perror_exit();
	path->name = name;
	path->ino = ino;
	path->pstat = 0;
	if (ISFLAG_RR(g_flags) || ISFLAG_L(g_flags))
	{
		if ((path->pstat = (struct stat *)malloc(sizeof(struct stat))) == 0)
			perror_exit();
		if (stat(name, path->pstat) == -1)
			perror_exit();
	}
	elem->content = (void *)path;
	elem->content_size = sizeof(*path);
	elem->next = 0;
	ft_lstins(names, elem, &sort);
	if (ISFLAG_RR(g_flags) && ISDIR(path->pstat->st_mode) &&
		ft_strcmp("..", name) != 0 && ft_strcmp(".", name) != 0)
		return (tlstdup(elem));
	return (0);
}

// READ THIS!!!!!!!!!!!!!!!!!
// For -R and recursion implementation
// DO NOT include directories ".." to lists!
void	list_dir(t_list *lst)
{
	DIR				*dstr;
	struct dirent	*dirp;
	t_list			*names;
	t_list			*subdirs;
	t_list			*tmp;

	errno = 0;
	if ((dstr = opendir(VP(lst->content)->name)) == 0)
		perror_exit();
	names = 0;
	subdirs = 0;
//	if (print_dir)
//		ft_printf("%s:\n", VP(lst->content)->name);
	while ((dirp = readdir(dstr)) != 0)
	{
		if (*(dirp->d_name) == '.' && !ISFLAG_A(g_flags))
			continue ;
		tmp = pathtolist(add_parent(dirp->d_name, VP(lst->content)->name),
				dirp->d_ino, &names);
		if (ISFLAG_RR(g_flags) && tmp)
			ft_lstins(&subdirs, tmp, &sort);
	}
	if (errno != 0 && dirp == 0)
		perror_exit();
	list_files(names);
	ft_lstdel(&names, &free_path);
	closedir(dstr);

	if (subdirs)
	{
//		ft_printf("\nRECURSION...\n");
		ft_lstiter(subdirs, &list_dir);
	}
	ft_lstdel(&subdirs, &free_path);
}
