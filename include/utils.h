/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:34:27 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/24 23:24:19 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "context.h"
# include <stdbool.h>

bool	is_existing_directory(const char *path);

void	perror_verbose(t_context *ctx, const char *cmd,
			const char *description);
void	print_error_verbose(t_context *ctx, const char *cmd,
			const char *loc, const char *msg);
void	print_quoted_error(t_context *ctx, const char *cmd,
			const char *loc, const char *msg);
void	print_simple_error(t_context *ctx, const char *cmd, const char *msg);

#endif
