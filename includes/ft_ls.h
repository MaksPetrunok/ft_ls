/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 21:12:58 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 15:23:19 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "funcs.h"
# include "colors.h"
# include "flags.h"

# include <sys/xattr.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/acl.h>

# define PROGRAM_NAME	"ft_ls"

# define VP(X) ((t_path *)(X))

# define PATH_BUFF_SIZE 4096

# define COL_OFFSET	2
# define STDIN	0
# define STDOUT 1
# define STDERR 2

# define PERM_R 'r'
# define PERM_W 'w'
# define PERM_X 'x'
# define PERM_N '-'

#endif
