/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/05 21:30:07 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
			error_option(*s);
		s++;
	}
}

static void	pathtolist(char *name, t_list **files, t_list **dirs)
{
	t_list		*elem;
	t_path		*path;
	struct stat	*buff;

	elem = malloc(sizeof(t_list));
	buff = malloc(sizeof(struct stat));
	path = malloc(sizeof(t_path));
	if (!buff || !path || !elem)
		perror_exit();
	if (stat(name, buff) == -1)
		perror_exit();
	path->name = ft_strdup(name);
	path->ino = buff->st_ino;
	path->pstat = buff;
	elem->content = (void *)path;
	elem->content_size = sizeof(*path);
	elem->next = 0;
	if (ISDIR(buff->st_mode))
		ft_lstins(dirs, elem, &sort);
	else
		ft_lstins(files, elem, &sort);
}

int			main(int ac, char **av)
{
	t_list	*filelst;
	t_list	*dirlst;

	g_flags = 0;
	filelst = 0;
	dirlst = 0;
	while (--ac > 0)
		if (av[ac][0] == '-')
			parse_flags(av[ac] + 1);
		else
			pathtolist(av[ac], &filelst, &dirlst);
	if (!filelst && !dirlst)
		pathtolist(".", &filelst, &dirlst);
//ft_printf("HERE\n");
	list_initial(filelst, dirlst);
	ft_lstdel(&dirlst, &free_path);
//system("leaks ft_ls");
	return (0);
}
