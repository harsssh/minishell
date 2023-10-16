/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 03:25:00 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 03:25:18 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "variables.h"
#include <stdlib.h>
#include <unistd.h>

void	sync_working_directory(struct s_context *ctx, char *for_whom)
{
	free(ctx->cwd);
	ctx->cwd = getcwd(NULL, 0);
	if (ctx->cwd == NULL)
		ft_dprintf(STDERR_FILENO,
			"%s: getcwd: cannot access parent directories: %s\n",
			for_whom, strerror(errno));
}

// This function sets `ctx->cwd` and returns its copy
char	*get_working_directory(struct s_context *ctx, char *for_whom)
{
	if (ctx->cwd == NULL)
	{
		sync_working_directory(ctx, for_whom);
		if (ctx->cwd == NULL)
			return (NULL);
	}
	return (ft_strdup(ctx->cwd));
}

int	bindpwd(t_context *ctx)
{
	char	*dirname;
	int		result;

	dirname = get_working_directory(ctx, "cd");
	if (dirname == NULL)
		return (EXIT_FAILURE);
	if (setvar(ctx, "PWD", dirname, 1) == 0)
		result = EXIT_SUCCESS;
	else
		result = EXIT_FAILURE;
	free(dirname);
	return (result);
}
