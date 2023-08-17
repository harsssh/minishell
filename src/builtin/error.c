/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:32 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 01:14:25 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void	perror_builtin(t_context *ctx, const char *cmd, const char *prefix)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
		ctx->shell_name, cmd, prefix, strerror(errno));
}

void	print_error_builtin(t_context *ctx, const char *cmd, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", ctx->shell_name, cmd, msg);
}

void	print_custom_error_builtin(t_context *ctx, const char *cmd,
		const char *loc, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
		ctx->shell_name, cmd, loc, msg);
}
