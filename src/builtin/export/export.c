/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:17:10 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 22:23:54 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin/builtin_internal.h"
#include "export_internal.h"
#include <stdlib.h>

static char	**skip_options(char **args)
{
	int	c;

	reset_get_next_option();
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

int	builtin_export(t_context *ctx, char **args)
{
	int	status;

	args = skip_options(args);
	if (*args == NULL)
		return (builtin_export_no_arg(ctx));
	status = EXIT_SUCCESS;
	while (*args)
	{
		if (export_each_arg(ctx, *args) == EXIT_FAILURE)
			status = EXIT_FAILURE;
		++args;
	}
	return (status);
}
