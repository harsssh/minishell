/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:32 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 20:19:58 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void	builtin_write_error(t_context *ctx, const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: write error: %s\n",
		ctx->shell_name, cmd_name, strerror(errno));
}

void	builtin_stdout_error(t_context *ctx, const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: stdout: %s\n",
		ctx->shell_name, cmd_name, strerror(errno));
}

void	builtin_not_implemented(t_context *ctx, const char *cmd_name)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: not implemented\n",
		ctx->shell_name, cmd_name);
}
