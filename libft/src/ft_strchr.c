/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:56:47 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/04 15:56:49 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	if (c == 0)
		return (0);
	ch = (char)c;
	while (*s && *s != ch)
		s++;
	return ((*s) ? (char *)s : 0);
}

// rm
/*
char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s == (char)c)
			return ((char *)s);
		else
			s++;
	return ((c == 0) ? (char *)s : 0);
}

*/
