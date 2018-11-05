/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:13:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/01 16:15:17 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_path(void *content, size_t size)
{
	t_path  *tmp;

	(void)size;
	tmp = (t_path *)content;
	free((void *)(tmp->name));
	free((void *)(tmp->pstat));
	free((void *)tmp);
}
