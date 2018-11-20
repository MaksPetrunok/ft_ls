/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:55:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/20 21:39:43 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned long int	g_flags;

static void	set_flag(long f)
{
	g_flags |= f;
	if (ISFLAG_L(f))
		g_flags &= ~(F_CC | F_X | F_1 | F_M);
	else if (ISFLAG_1(f))
		g_flags &= ~(F_CC | F_X | F_L | F_M);
	else if (ISFLAG_X(f))
		g_flags &= ~(F_CC | F_1 | F_L);
	else if (ISFLAG_CC(f))
		g_flags &= ~(F_1 | F_X | F_L);
	else if (ISFLAG_M(f))
		g_flags &= ~(F_CC | F_1 | F_X | F_L);
// TEST HOW -l1xCm flags are parsed before release
}

static int	parse_flags(char *s, int *f)
{
	char	*ref;
	char	*p;
	char	*tmp;

	tmp = s + 1;
	if (*tmp == '\0')
		return (0);
	if (*tmp == '-' && *(tmp + 1) == '\0')
	{
		*f = 0;
		return (1);
	}
	ref = FLAGS;
	while (*tmp)
	{
		if ((p = ft_strchr(ref, *tmp)) != 0)
			set_flag(1U << (long)(p - ref));
		else
			error_option(*tmp);
		tmp++;
	}
	return (1);
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
	if ((ISFLAG_LL(g_flags) ? stat(name, buff) : lstat(name, buff)) == -1)
	{
		perror_report(name);
		return (1);
	}
	path->name = ft_strdup(name);
	path->path = ft_strcmp("/", name) ? ft_strdup(name) : ft_strnew(0);
	path->ino = buff->st_ino;
	path->pstat = buff;
	path->xat_acl = 0;
	elem->content = (void *)path;
	elem->content_size = sizeof(*path);
	elem->next = 0;
	ft_lstins((ISDIR(buff->st_mode) && !ISFLAG_D(g_flags)) ?
		dirs : files, elem, &sort);
	return (1);
}

int			main(int ac, char **av)
{
	t_list	*filelst;
	t_list	*dirlst;
	int		parsed_path;
	int		i;
	int		on_flags;

	g_flags = 0;
	filelst = 0;
	dirlst = 0;
	parsed_path = 0;
	on_flags = 1;
	i = 1;
	while (i < ac && on_flags)
		if (av[i][0] == '-' && parse_flags(av[i], &on_flags))
			i++;
		else
			break ;
	while (i < ac)
		parsed_path += pathtolist(av[i++], &filelst, &dirlst);
	if (!parsed_path)
		pathtolist(".", &filelst, &dirlst);
	process_input(filelst, dirlst, parsed_path);
//system("leaks ft_ls");
	return (0);
}
