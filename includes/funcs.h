/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:18:34 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 16:26:44 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

# include "libft.h"
# include "struct.h"

void	set_color(mode_t mode);

char	get_type(mode_t mode);
char	*get_size(struct stat *st, char *buff);
char	*get_owner(uid_t uid);
char	*get_group(gid_t gid);
void	get_acc(char *buff, t_path *path);

void	init_fmt(t_dout *fmt);
void	fill_fmt(t_dout *fmt, t_list *lst);

void	free_path(void *content, size_t size);
void	free_arr(t_out **arr);

void	iter_dirs(t_list *dirs, int print_dir_name);
void	process_input(t_list *files, t_list *dirs, int print_dir);
void	list_files(t_list *lst, int total);
void	list_dir(t_list *lst);

void	perror_exit(const char *s);
void	perror_report(const char *s);
void	error_option(char c);

int		sort(void *a, void *b);
t_out	**list_to_arr(t_list *lst, int *max_ino, int *max_name);

void	get_path(char *name, t_path *buff);
void	print_paths(t_list *lst, int printdirname);
void	print_table(t_list *lst);
void	print_tablex(t_list *lst);
void	print_det_lst(t_list *lst, int total);

char	*add_parent(const char *name, const char *parent);

#endif
