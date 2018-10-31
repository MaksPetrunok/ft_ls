/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/31 21:21:15 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //remove
#include "ft_ls.h"

static void	parse_flags(char *s, unsigned long int *fl)
{
	char	*ref;
	char	*p;

	ref = FLAGS;
	while (*s)
	{
		if ((p = ft_strchr(ref, *s)) != 0)
			*fl |= 1U << (int)(p - ref);
		else
		{
			ft_printf("ft_ls: invalid option -- '%c'\n", *s);
			exit(1); // handle errno !!!
		}
		s++;
	}
}

/*
static void	list_dir(char *path, unsigned long flags)
{
	
	//While listing files and dirs, check if ISDIR(path) && -R. If so - call process_path.
	
}
*/
static void	process_path(char *path, unsigned long flags)
{
//	DIR	*dstr = opendir(path);
//	struct dirent	*dirp;
	struct stat		path_stat;
	
	if (stat(path, &path_stat) == -1)
	{
		ft_printf("Error occured in stat() function.\n");
		exit(1);
	}
	ft_printf("Path:      %s\n", path);
	ft_printf("Flags:     %lu\n", flags);
	ft_printf("Path type: %#o\n", path_stat.st_mode);

// if ISDIR(path) - list directory content
// else - print path (with properties if required by flags)


	
/*
	while ((dirp = readdir(dstr)) != 0)
	{
		printf(" > %s\n", dirp->d_name);
		printf("sizeof(struct dir) = %ld\n", sizeof(*dirp));
	}
	while ((dirp = readdir(d)) != 0)
	{
		ft_printf("Directory name: %s\n", dirp->d_name);
		ft_printf("inode:          %lu\n", (unsigned long)(dirp->d_ino));
		if (stat(dirp->d_name, &path_stat))
		{
			ft_printf("inode(stat):    %lu\n", (unsigned long)path_stat.st_ino);
			ft_printf("uid:            %lu\n", (unsigned long)path_stat.st_uid);
			ft_printf("size:           %lu\n", (unsigned long)path_stat.st_size);
			ft_printf("mode:           %o\n", (unsigned long)path_stat.st_mode);
			ft_printf("\n");
		}
	}
	
	if (ISDIR(path_stat.st_mode) && ISFLAG_R(flags))
		for each path in directory - process_path() 
*/
}

void	iter_paths(t_list *lst, unsigned long flags)
{
	int	flag;

	flag = ft_lstsize(lst) > 1;
	while (lst)
	{
		process_path((char *)(lst->content), flags);
		write(1, "\n", flag);
		lst = lst->next;
	}
}

int main(int ac, char **av)
{
	t_list			*files;
	unsigned long	flags;

	files = 0;
	flags = 0;
	while (--ac > 0)
	{
		if (av[ac][0] == '-')
			parse_flags(av[ac] + 1, &flags);
		else
		{
			if (files == 0)
				files = ft_lstnew(av[ac], ft_strlen(av[ac]) + 1);
			else
				ft_lstadd(&files, ft_lstnew(av[ac], ft_strlen(av[ac]) + 1));
		}
	}
	if (files == 0)
		files = ft_lstnew(".", 2);
	iter_paths(files, flags);
//	ft_printf("Total files: %d\n", ft_lstsize(files));
//	printf("Flags parsed: %lu\n", flags);
	ft_lstfree(&files);
	return (0);
}
