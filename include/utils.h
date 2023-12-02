/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:34:27 by kemizuki          #+#    #+#             */
/*   Updated: 2023/11/30 01:37:13 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "context.h"
# include "ft_list.h"
# include "errno.h"
# include <stdbool.h>
# include <string.h>

// fs.c
bool	is_existing_directory(const char *path);
bool	is_absolute_path(const char *path);
char	*join_path(const char *base, const char *relpath);

// list.c
char	**list_to_string_array(t_list *list, char *(*f)(void *data));

// memory.c
void	destroy_string_array(char **array);

// error.c
void	perror_verbose(t_context *ctx, const char *cmd,
			const char *description);
void	print_error_verbose(t_context *ctx, const char *cmd,
			const char *loc, const char *msg);
void	print_quoted_error(t_context *ctx, const char *cmd,
			const char *loc, const char *msg);
void	print_simple_error(t_context *ctx, const char *cmd, const char *msg);

// directory.c
void	sync_working_directory(struct s_context *ctx, char *for_whom);
char	*get_working_directory(struct s_context *ctx, char *for_whom);
int		bindpwd(t_context *ctx);

// message.c
void	display_exit_message(t_context *ctx);

// char.c
bool	is_quote(int c);

#endif
