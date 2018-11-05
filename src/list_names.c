/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/01 17:10:55 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_files(t_list *lst)
{
	while (lst)
	{
		if (ISFLAG_I(g_flags))
			ft_printf("%d %s\n", VP(lst->content)->ino, VP(lst->content)->name);
		else
			ft_printf("%s\n", VP(lst->content)->name);
		lst = lst->next;
	}
}

static t_list *tlstdup(t_list *elem)
{
	t_list	*lst;
	void	*cnt;

	lst = (t_list *)malloc(sizeof(t_list));
	cnt = malloc(elem->content_size);
	if (!(lst && cnt))
		perror_exit();
	lst->content = cnt;
	lst->next = 0;
	lst->content_size = elem->content_size;
	ft_memcpy(lst->content, elem->content, elem->content_size);
	return (lst);
}

static t_list	*pathtolist(char *name, int ino, t_list **names)
{
	t_list		*elem;
	t_path		*path;

	path = (t_path *)malloc(sizeof(t_path));
	if (!path)
		perror_exit();
	if ((path->name = ft_strdup(name)) == 0)
		perror_exit();
	path->ino = ino;
	path->pstat = 0;
	if (ISFLAG_RR(g_flags))
	{
		if ((path->pstat = (struct stat *)malloc(sizeof(struct stat))) == 0)
			perror_exit();
		if (stat(name, path->pstat) == -1)
		{
			perror_exit();
		}
	}
	if ((elem = ft_lstnew((void *)path, sizeof(path))) == 0)
		perror_exit();
	ft_lstins(names, elem, &sort);
	free((void *)path);
	if (ISFLAG_RR(g_flags) && ISDIR(path->pstat->st_mode) &&
		ft_strcmp("..", name) != 0 && ft_strcmp(".", name) != 0)
	{
		return (tlstdup(elem));
	}
	return (0);
}

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
	while ((dirp = readdir(dstr)) != 0)
	{
		tmp = pathtolist(add_parent(dirp->d_name, VP(lst->content)->name), dirp->d_ino, &names);
		if (ISFLAG_RR(g_flags) && tmp && ft_strcmp("..", dirp->d_name) != 0 && ft_strcmp(".", dirp->d_name))
		{
errno = 0;
//			VP(tmp->content)->name =
//			ft_strjoin(VP(lst->content)->name, ft_strjoin("/", VP(tmp->content)->name));
			ft_lstins(&subdirs, tmp, &sort);
			if (errno)
				perror_exit();
		}
		else
			free((void *)tmp);
//		ft_printf("%s ", dirp->d_name);
	}
	if (errno != 0 && dirp == 0)
		perror_exit();
	list_files(names);
	closedir(dstr);
//ft_printf("\n>>>LISTING OF DIRECTORIES:\n");
//	list_files(subdirs);
//ft_printf("RECURSION... subdirs=%p\n", subdirs);
	if (subdirs)
		ft_lstiter(subdirs, &list_dir);
}
