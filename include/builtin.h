/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:35:06 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/17 22:19:46 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "context.h"

int	builtin_echo(t_context *ctx, char **args);
int	builtin_env(t_context *ctx, char **args);
int	builtin_unset(t_context *ctx, char **args);
int	builtin_exit(t_context *ctx, char **args);
int	builtin_export(t_context *ctx, char **args);
int	builtin_pwd(t_context *ctx, char **args);
int	builtin_cd(t_context *ctx, char **args);

#endif
