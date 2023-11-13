/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:20:07 by kemizuki          #+#    #+#             */
/*   Updated: 2023/11/13 17:07:22 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins_internal.h"
#include "cd_internal.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

static void	set_working_directory(t_context *ctx, const char *path)
{
	free(ctx->cwd);
	ctx->cwd = ft_strdup(path);
}

// return true if success
bool	get_absolute_destination_path(t_context *ctx, const char *newdir,
		char **result)
{
	char	*abspath;

	if (ctx->cwd == NULL)
		sync_working_directory(ctx, "chdir");
	if (is_absolute_path(newdir))
		abspath = ft_strdup(newdir);
	else
		abspath = join_path(ctx->cwd, newdir);
	*result = canonicalize_absolute_path(abspath, true);
	if (*result == NULL || **result == '\0')
	{
		free(*result);
		*result = abspath;
		return (false);
	}
	free(abspath);
	return (true);
}

static int	retry_chdir(t_context *ctx, const char *newdir)
{
	int		ret;
	char	*cwd_on_failure;

	ret = chdir(newdir);
	if (ret == 0)
	{
		cwd_on_failure = join_path(ctx->cwd, newdir);
		if (cwd_on_failure == NULL)
			return (-1);
		sync_working_directory(ctx, "cd");
		if (ctx->cwd == NULL)
			set_working_directory(ctx, cwd_on_failure);
		free(cwd_on_failure);
	}
	return (ret);
}

// return the value of chdir
int	change_directory(t_context *ctx, const char *newdir)
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
	else
		ret = retry_chdir(ctx, newdir);
	free(path);
	return (ret);
}
