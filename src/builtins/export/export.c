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

int	builtin_export(t_context *ctx, char **args)
{
	int	status;

	args = ignore_options(args);
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
