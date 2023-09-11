/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:17:39 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 19:17:44 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_INTERNAL_H
# define EXPORT_INTERNAL_H

# include "context.h"

int	builtin_export_no_arg(t_context *ctx);
int	export_each_arg(t_context *ctx, char *arg);

#endif
