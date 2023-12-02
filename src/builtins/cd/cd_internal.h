/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:19:50 by kemizuki          #+#    #+#             */
/*   Updated: 2023/12/03 00:03:14 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_INTERNAL_H
# define CD_INTERNAL_H

# include "context.h"

typedef struct s_proc_state
{
	const char	*path;
	char		*result;
	char		*cur;
	bool		check_existence;
}	t_proc_state;

typedef t_proc_state	(*t_handler)(t_proc_state);

int		change_directory(t_context *ctx, const char *newdir);
char	*canonicalize_absolute_path(const char *path, bool check_existence);

#endif
