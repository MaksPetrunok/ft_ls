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
	struct stat	*pstat;

	pstat = (struct stat *)malloc(sizeof(struct stat));
	path = (t_path *)malloc(sizeof(t_path));
	if (!pstat || !path)
		perror_exit();
	if (stat(name, pstat) == -1)
		perror_exit();
	path->name = ft_strdup(name);
	path->ino = pstat->st_ino;
	path->pstat = pstat;
	if ((elem = ft_lstnew((void *)path, sizeof(path))) == 0)
		perror_exit();
	if (ISDIR(pstat->st_mode))
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
	list_initial(filelst, dirlst);
	ft_lstdel(&dirlst, &free_path);
//system("leaks ft_ls");
	return (0);
}
