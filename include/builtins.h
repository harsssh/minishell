/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:35:06 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 15:16:05 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "context.h"

typedef int		(*t_builtin_func)(t_context *ctx, const char **argv);

t_builtin_func	get_builtin_func(char *cmd_name);

int				builtins_echo(t_context *ctx, const char **argv);
int				builtins_env(t_context *ctx, const char **argv);
int				builtins_unset(t_context *ctx, const char **argv);
int				builtins_exit(t_context *ctx, const char **argv);
int				builtins_export(t_context *ctx, const char **argv);
int				builtins_pwd(t_context *ctx, const char **argv);
int				builtins_cd(t_context *ctx, const char **argv);

#endif
