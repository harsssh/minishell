/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:53:17 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/20 17:21:41 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	**ignore_options(char **args)
{
	int	c;

	init_get_next_option();
	while (*args)
	{
		c = get_next_option(*args, "");
		if (c == END_OF_OPTIONS)
			break ;
		if (c == END_OF_ARG)
			++args;
	}
	return (args);
}

void	sync_working_directory(t_context *ctx, char *for_whom)
{
	free(ctx->cwd);
	ctx->cwd = getcwd(NULL, 0);
	if (ctx->cwd == NULL)
		ft_dprintf(STDERR_FILENO,
			"%s: getcwd: cannot access parent directories: %s\n",
			for_whom,
			strerror(errno));
}

// This function sets `ctx->cwd` and returns its copy
char	*get_working_directory(t_context *ctx, char *for_whom)
{
	if (ctx->cwd == NULL)
	{
		sync_working_directory(ctx, for_whom);
		if (ctx->cwd == NULL)
			return (NULL);
	}
	return (ft_strdup(ctx->cwd));
}
