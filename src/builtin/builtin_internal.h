/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:23 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 20:19:24 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INTERNAL_H
# define BUILTIN_INTERNAL_H

# include "context.h"

# define END_OF_ARG		(-1)
# define END_OF_OPTIONS (-2)
# define ILLEGAL_OPTION (-3)

void	builtin_write_error(t_context *ctx, const char *cmd_name);
void	builtin_stdout_error(t_context *ctx, const char *cmd_name);
void	builtin_not_implemented(t_context *ctx, const char *cmd_name);

void	reset_get_next_option(void);
int		get_next_option(char *arg, const char *optstring);

#endif
