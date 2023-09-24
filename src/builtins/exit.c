/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 01:22:58 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 01:22:59 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins_internal.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_status_or_exit(t_context *ctx, const char **argv)
{
	int	status;

	if (*argv == NULL)
		exit(ctx->last_exit_status & 0xFF);
	errno = 0;
	status = ft_atoi(*argv) & 0xFF;
	if (errno)
	{
		print_error_verbose(ctx, "exit", *argv, ERR_NUM_REQUIRED);
		exit(2);
	}
	if (argv[1] == NULL)
		exit(status);
	print_simple_error(ctx, "exit", ERR_TOO_MANY_ARG);
	if (ctx->last_exit_status == 0)
		return (1);
	return (ctx->last_exit_status & 0xFF);
}

// TODO: Assumes a non-login, interactive shell context
int	builtins_exit(t_context *ctx, const char **argv)
{
	if (*argv && ft_strcmp(*argv, "--") == 0)
		++argv;
	ft_putendl_fd("exit", STDERR_FILENO);
	return (get_status_or_exit(ctx, argv));
}
