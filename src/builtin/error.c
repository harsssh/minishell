/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:32 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 17:50:52 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

static void	error_prolog(t_context *ctx, const char *cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: ", ctx->shell_name, cmd);
}

void	perror_builtin(t_context *ctx, const char *cmd, const char *prefix)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "%s: %s\n", prefix, strerror(errno));
}

void	print_error_builtin(t_context *ctx, const char *cmd,
		const char *loc, const char *msg)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "%s: %s\n", loc, msg);
}

void	print_simple_error_builtin(t_context *ctx, const char *cmd,
		const char *msg)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
}

void	print_quoted_error_builtin(t_context *ctx, const char *cmd,
		const char *loc, const char *msg)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "`%s': %s\n", loc, msg);
}
