/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:13:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/05 20:44:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_path(void *content, size_t size)
{
	t_path  *tmp;

	(void)size;
	tmp = (t_path *)content;
	free((void *)(tmp->name));
//printf("tmp->name: %s freed, next %p\n",tmp->name, tmp->pstat);
	free((void *)(tmp->pstat));
//printf("tmp->pstat freed\n");
	free(content);
//printf("tmp       freed\n");
}
