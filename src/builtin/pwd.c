/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:34:42 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/19 02:34:44 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_internal.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// This function sets `ctx->cwd` and returns its copy
static char *get_working_directory(t_context *ctx, char *for_whom)
{
	if (ctx->cwd == NULL)
	{
		ctx->cwd = getcwd(NULL, 0);
		if (ctx->cwd == NULL)
		{
			ft_dprintf(STDERR_FILENO,
					   "%s: getcwd: cannot access parent directories: %s\n",
					   for_whom, strerror(errno));
			return (NULL);
		}
	}
	return (ft_strdup(ctx->cwd));
}

int	builtin_pwd(t_context *ctx, char **args)
{
	char	*directory;

	args = ignore_options(args);
	directory = get_working_directory(ctx, "pwd");
	if (directory == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd(directory, STDOUT_FILENO);
	free(directory);
	return (EXIT_SUCCESS);
}
