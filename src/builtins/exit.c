/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 01:22:58 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/30 01:52:29 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins_internal.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_status_or_exit(t_context *ctx, const char **args)
{
	int	status;

	if (*args == NULL)
		exit(ctx->last_exit_status & 0xFF);
	errno = 0;
	status = ft_atoi(*args) & 0xFF;
	if (errno)
	{
		print_error_verbose(ctx, "exit", *args, ERR_NUM_REQUIRED);
		exit(2);
	}
	if (args[1] == NULL)
		exit(status);
	print_simple_error(ctx, "exit", ERR_TOO_MANY_ARG);
	if (ctx->last_exit_status == 0)
		return (1);
	return (ctx->last_exit_status & 0xFF);
}

int	builtins_exit(t_context *ctx, const char **args)
{
	if (*args && ft_strcmp(*args, "--") == 0)
		++args;
	display_exit_message(ctx);
	return (get_status_or_exit(ctx, args));
}
