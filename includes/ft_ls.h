/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 21:12:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/31 21:13:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define FLAGS	"alrRt"

# define F_A	1U << 0 
# define F_L	1U << 1
# define F_R	1U << 2
# define F_RR	1U << 3
# define F_T	1U << 4

#endif
