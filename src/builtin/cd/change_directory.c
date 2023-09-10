/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:20:07 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/20 17:21:00 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin_internal.h"
#include "cd_internal.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	set_working_directory(t_context *ctx, char *path)
{
	free(ctx->cwd);
	ctx->cwd = ft_strdup(path);
}

static bool	is_absolute_path(const char *path)
{
	return (*path == '/');
}

// return true if success
bool	get_absolute_destination_path(t_context *ctx, char *newdir,
		char **result)
{
	char	*abspath;

	if (ctx->cwd == NULL)
		sync_working_directory(ctx, "chdir");
	if (is_absolute_path(newdir))
		abspath = ft_strdup(newdir);
	else
		abspath = join_path(ctx->cwd, newdir);
	*result = canonicalize_path(abspath, true);
	if (*result == NULL || **result == '\0')
	{
		free(*result);
		*result = abspath;
		return (false);
	}
	free(abspath);
	return (true);
}

// return the value of chdir
int	change_directory(t_context *ctx, char *newdir)
{
	int		ret;
	char	*path;
	bool	is_canon_success;

	is_canon_success = get_absolute_destination_path(ctx, newdir, &path);
	ret = chdir(path);
	if (ret == 0)
	{
		if (!is_canon_success)
			sync_working_directory(ctx, "cd");
		if (is_canon_success || ctx->cwd == NULL)
			set_working_directory(ctx, path);
	}
	free(path);
	return (ret);
}
