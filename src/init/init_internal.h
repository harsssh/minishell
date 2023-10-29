/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:09:01 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/30 01:26:42 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_INTERNAL_H
# define INIT_INTERNAL_H

# include "context.h"

int	inherit_env(t_context *ctx, char **envp);

#endif
