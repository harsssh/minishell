/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:19:50 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/20 17:19:52 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_INTERNAL_H
# define CD_INTERNAL_H

# include "context.h"

int		change_directory(t_context *ctx, char *newdir);
char	*join_path(char *base, char *relpath);
char	*canonicalize_absolute_path(const char *path, bool check_existence);

#endif
