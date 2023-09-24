/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:32 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/24 22:27:42 by kemizuki         ###   ########.fr       */
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

/*
 * example:
 * - minishell: echo: write error: Bad file descriptor
 */
void	perror_verbose(t_context *ctx, const char *cmd, const char *description)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "%s: %s\n", description, strerror(errno));
}

/*
 * example:
 * - minishell: exit: foo: numeric argument required
 */
void	print_error_verbose(t_context *ctx, const char *cmd,
							const char *loc, const char *msg)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "%s: %s\n", loc, msg);
}

/*
 * example:
 * - minishell: exit: too many arguments
 */
void	print_simple_error(t_context *ctx, const char *cmd, const char *msg)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
}

/*
 * example:
 * - minishell: env: `=': not a valid identifier
 */
void	print_quoted_error(t_context *ctx, const char *cmd,
							const char *loc, const char *msg)
{
	error_prolog(ctx, cmd);
	ft_dprintf(STDERR_FILENO, "`%s': %s\n", loc, msg);
}
