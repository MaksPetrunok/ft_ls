/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/01 17:10:55 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define ISDIR(X) (0040000 & X)

unsigned long int	g_flags;

static void	parse_flags(char *s)
{
	char	*ref;
	char	*p;

	ref = FLAGS;
	while (*s)
	{
		if ((p = ft_strchr(ref, *s)) != 0)
			g_flags |= 1U << (int)(p - ref);
		else
		{
			ft_dprintf(2,
			"ft_ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",
			*s, FLAGS);
			exit(1);
		}
		s++;
	}
}

static void	list_dir(char *path, t_list **subdirlst)
{
	DIR				*dstr;
	struct dirent	*dirp;
	struct stat		path_stat;

	errno = 0;
	if ((dstr = opendir(path)) == 0)
		perror_exit();
	errno = 0;
	while ((dirp = readdir(dstr)) != 0)
	{
		ft_printf(">%-15s\n", dirp->d_name);
		errno = 0;
		//whole lotta LEAKS from double ft_strjoin():
		char *s = ft_strjoin(path, ft_strjoin("/", dirp->d_name));
		if (stat(s, &path_stat) == -1)
			perror_exit();

		if (ISFLAG_RR(g_flags) && ISDIR(path_stat.st_mode))
		{
			ft_lstadd(subdirlst,
				ft_lstnew((void *)s, ft_strlen(s) + 1));
		}

	}
	if (errno != 0 && dirp == 0)
		perror_exit();
	closedir(dstr);
}

static void	process_path(char *path)
{
	struct stat		path_stat;
	t_list			*subdirlst;
	
	subdirlst = 0;
	errno = 0;
	if (stat(path, &path_stat) == -1)
		perror_exit();
	if ISDIR(path_stat.st_mode)
		list_dir(path, &subdirlst);
	else
		ft_printf("%s\n", path);

	if (ISFLAG_RR(g_flags) && subdirlst != 0)
	{
		iter_paths(subdirlst);
		ft_lstfree(&subdirlst);
	}
}

void	iter_paths(t_list *lst)
{
	int	size;

	size = ft_lstsize(lst);
	while (lst)
	{
		process_path((char *)(lst->content));
		write(1, "\n", size-- > 1);
		lst = lst->next;
	}
}

int main(int ac, char **av)
{
	t_list			*files;

	files = 0;
	g_flags = 0;
	while (--ac > 0)
		if (av[ac][0] == '-')
			parse_flags(av[ac] + 1);
		else
			ft_lstadd(&files, ft_lstnew(av[ac], ft_strlen(av[ac]) + 1));
	if (files == 0)
		files = ft_lstnew(".", 2);
	iter_paths(files);
	ft_lstfree(&files);
//system("leaks ft_ls");
	return (0);
}
