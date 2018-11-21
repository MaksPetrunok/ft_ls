/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:25:15 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 16:25:40 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*add_parent(const char *name, const char *parent)
{
	char	*dir;
	char	*res;

	if ((dir = ft_strjoin(parent, "/")) == 0)
		perror_exit("");
	if ((res = ft_strjoin(dir, name)) == 0)
		perror_exit("");
	free((void *)dir);
	return (res);
}
