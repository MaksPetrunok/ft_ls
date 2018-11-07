/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/07 14:43:21 by mpetruno         ###   ########.fr       */
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

static int	pathtolist(char *name, t_list **files, t_list **dirs)
{
	t_list		*elem;
	t_path		*path;
	struct stat	*buff;

	elem = malloc(sizeof(t_list));
	buff = malloc(sizeof(struct stat));
	path = malloc(sizeof(t_path));
	if (!buff || !path || !elem)
		perror_exit("");
	if (ISFLAG_LL(g_flags) ? stat(name, buff) == -1 : lstat(name, buff) == -1)
	{
		perror_report(name);
		return (1);
	}
	path->name = ft_strdup(name);
	path->path = ft_strcmp("/", name) ? ft_strdup(name) : ft_strnew(0);
	path->ino = buff->st_ino;
	path->pstat = buff;
	elem->content = (void *)path;
	elem->content_size = sizeof(*path);
	elem->next = 0;
	if (ISDIR(buff->st_mode))
		ft_lstins(dirs, elem, &sort);
	else
		ft_lstins(files, elem, &sort);
	return (1);
}

int			main(int ac, char **av)
{
	t_list	*filelst;
	t_list	*dirlst;
	int		parsed_path;

	g_flags = 0;
	filelst = 0;
	dirlst = 0;
	parsed_path = 0;
	while (--ac > 0)
		if (av[ac][0] == '-')
			parse_flags(av[ac] + 1);
		else
			parsed_path += pathtolist(av[ac], &filelst, &dirlst);
	if (!parsed_path)
		pathtolist(".", &filelst, &dirlst);
	process_input(filelst, dirlst);
//system("leaks ft_ls");
	return (0);
}
