/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:42:39 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/09 18:29:51 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_out		**list_to_arr(t_list *lst, int *max_ino, int *max_name)
{
	t_out	**arr;
	int		index;

	index = 0;
	if ((arr = (t_out **)malloc(sizeof(t_out **) * (ft_lstsize(lst) + 1))) == 0)
		perror_exit("");
	while (lst)
	{
		if ((arr[index] = malloc(sizeof(t_out))) == 0)
			perror_exit("");
		arr[index]->path = VP(lst->content);
		arr[index]->name_len = ft_strlen(arr[index]->path->name) + COL_OFFSET;
		arr[index]->ino_len = ISFLAG_I(g_flags) ?
								ft_numlen(arr[index]->path->ino) : 0;
		if (arr[index]->name_len > *max_name)
			*max_name = arr[index]->name_len;
		if (arr[index]->ino_len > *max_ino)
			*max_ino = arr[index]->ino_len;
		index++;
		lst = lst->next;
	}
	arr[index] = 0;
	return (arr);
}

static int	arrlen(t_out **arr)
{
	int	len;

	if (arr == 0)
		return (0);
	len = 0;
	while (*arr++)
		len++;
	return (len);
}

static void	print_array_v(t_out **arr, int col, int ino_w, int name_w)
{
	int	i;
	int	size;
	int	ind;
	int	col_len;

	size = arrlen(arr);
	col_len = size / col + (size % col > 0);
	i = -1;
	while (++i < col_len)
	{
		ind = i;
		while (ind < size)
		{
			if (ISFLAG_I(g_flags))
				ft_printf("%*d ", ino_w, arr[ind]->path->ino);
			ft_printf("%-*s",
				(ind + col_len >= size) ? 1 : name_w, arr[ind]->path->name);
			ind += col_len;
		}
		ft_printf("\n");
	}
}

static void	print_array_h(t_out **arr, int col, int ino_w, int name_w)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (ISFLAG_I(g_flags))
			ft_printf("%*d ", ino_w, arr[i]->path->ino);
		if ((i + 1) % col == 0 || arr[i + 1] == 0)
			ft_printf("%-*s\n", 1, arr[i]->path->name);
		else
			ft_printf("%-*s", name_w, arr[i]->path->name);
	}
}

void		print_table(t_list *lst)
{
	t_out			**arr;
	int				name_w;
	int				ino_w;
	struct winsize	ws;
	int				col;

	name_w = (COL_OFFSET) ? COL_OFFSET : 1;
	ino_w = 0;
	arr = list_to_arr(lst, &ino_w, &name_w);
	ino_w = (ino_w) ? ino_w + 1 : 0;
	if (ioctl((ISFLAG_CC(g_flags) || ISFLAG_X(g_flags)) ?
			STDIN : STDOUT, TIOCGWINSZ, &ws) != -1 && !ISFLAG_1(g_flags))
		col = (ws.ws_col - COL_OFFSET > ino_w + name_w) ?
				(ws.ws_col - COL_OFFSET) / (ino_w + name_w) : 1;
	else
		col = 1;
	name_w = (col > 1) ? name_w : 1;
	ino_w = (ino_w) ? ino_w - 1 : 0;
	if (ISFLAG_X(g_flags))
		print_array_h(arr, col, ino_w, name_w);
	else
		print_array_v(arr, col, ino_w, name_w);
	free_arr(arr);
}
