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

#include "builtins.h"
#include "builtins/builtins_internal.h"
#include "export_internal.h"
#include <stdlib.h>

int	builtins_export(t_context *ctx, const char **argv)
{
	int	status;

	argv = ignore_options(argv);
	if (*argv == NULL)
		return (builtin_export_no_arg(ctx));
	status = EXIT_SUCCESS;
	while (*argv)
	{
		if (export_each_arg(ctx, *argv) == EXIT_FAILURE)
			status = EXIT_FAILURE;
		++argv;
	}
	return (status);
}
