/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:17:23 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 19:17:24 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>

#define LINE_FORMAT_EXPORTED "declare -x %s=\"%s\"\n"
#define LINE_FORMAT_NO_VALUE "declare -x %s\n"

static void	print_env(void *data)
{
	t_variable	*var;

	var = (t_variable *)data;
	if (var->attributes & VAR_ATTR_EXPORTED)
	{
		if (var->attributes & VAR_ATTR_NO_VALUE)
			printf(LINE_FORMAT_NO_VALUE, var->name);
		else
			printf(LINE_FORMAT_EXPORTED, var->name, var->value);
	}
}

int	builtin_export_no_arg(t_context *ctx)
{
	ft_list_iter(ctx->variables, print_env);
	return (EXIT_SUCCESS);
}
