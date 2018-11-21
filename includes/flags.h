/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:14:16 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 15:15:50 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# define FLAGS	"ftuSRLlgmxC1ardiG"

# define F_F	0x0001
# define F_T	0x0002
# define F_U	0x0004
# define F_SS	0x0008
# define F_RR	0x0010
# define F_LL	0x0020
# define F_L	0x0040
# define F_G	0x0080
# define F_M	0x0100
# define F_X	0x0200
# define F_CC	0x0400
# define F_1	0x0800
# define F_A	0x1000
# define F_R	0x2000
# define F_D	0x4000
# define F_I	0x8000
# define F_GG	0x10000

# define F_OUTPUT_TYPE	0x0FC0
# define F_ST			0x100FE

# define ISFLAG_A(X)	(F_A & X)
# define ISFLAG_L(X)	(F_L & X)
# define ISFLAG_R(X)	(F_R & X)
# define ISFLAG_RR(X)	(F_RR & X)
# define ISFLAG_T(X)	(F_T & X)
# define ISFLAG_D(X)	(F_D & X)
# define ISFLAG_F(X)	(F_F & X)
# define ISFLAG_I(X)	(F_I & X)
# define ISFLAG_M(X)	(F_M & X)
# define ISFLAG_LL(X)	(F_LL & X)
# define ISFLAG_1(X)	(F_1 & X)
# define ISFLAG_X(X)	(F_X & X)
# define ISFLAG_CC(X)	(F_CC & X)
# define ISFLAG_U(X)	(F_U & X)
# define ISFLAG_G(X)	(F_G & X)
# define ISFLAG_SS(X)	(F_SS & X)
# define ISFLAG_GG(X)	(F_GG & X)
# define IS_STAT_REQ(X)	(F_ST & X)

# define ISFIFO(X)	((S_IFMT & X) == S_IFIFO)
# define ISCHR(X)	((S_IFMT & X) == S_IFCHR)
# define ISDIR(X)	((S_IFMT & X) == S_IFDIR)
# define ISBLK(X)	((S_IFMT & X) == S_IFBLK)
# define ISREG(X)	((S_IFMT & X) == S_IFREG)
# define ISLNK(X)	((S_IFMT & X) == S_IFLNK)
# define ISSOCK(X)	((S_IFMT & X) == S_IFSOCK)
# define ISWHT(X)	((S_IFMT & X) == S_IFWHT)

extern unsigned long int	g_flags;

#endif
