/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:35:06 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 19:27:17 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "context.h"

int	builtins_echo(t_context *ctx, char **args);
int	builtins_env(t_context *ctx, char **args);
int	builtins_unset(t_context *ctx, char **args);
int	builtins_exit(t_context *ctx, char **args);
int	builtins_export(t_context *ctx, char **args);
int	builtins_pwd(t_context *ctx, char **args);
int	builtins_cd(t_context *ctx, char **args);

#endif
