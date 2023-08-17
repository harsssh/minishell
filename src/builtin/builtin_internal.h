/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:23 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 01:15:49 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INTERNAL_H
# define BUILTIN_INTERNAL_H

# include "context.h"

# define ERR_TOO_MANY_ARG	"too many arguments"
# define ERR_NUM_REQUIRED	"numeric argument required"
# define ERR_WRITE			"write error"
# define ERR_NOT_IMPL		"not implemented"
# define ERR_STDOUT			"stdout"

# define END_OF_ARG		-1
# define END_OF_OPTIONS	-2
# define ILLEGAL_OPTION	-3

void	perror_builtin(t_context *ctx, const char *cmd, const char *prefix);
void	print_error_builtin(t_context *ctx, const char *cmd, const char *msg);
void	print_custom_error_builtin(t_context *ctx, const char *cmd,
			const char *loc, const char *msg);

void	reset_get_next_option(void);
int		get_next_option(char *arg, const char *optstring);

#endif
