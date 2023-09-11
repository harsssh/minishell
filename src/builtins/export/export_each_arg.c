/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_each_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:18:02 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 19:30:30 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins/builtins_internal.h"
#include "export_internal.h"
#include "libft.h"
#include "variables.h"
#include <stdlib.h>

static int	handle_only_identifier(
	t_context *ctx,
	t_parsed_variable_assignment result
)
{
	t_variable	*var;

	var = getvar(ctx, result.name);
	if (var == NULL)
	{
		setvar(ctx, result.name, "", 0);
		var = getvar(ctx, result.name);
		var->attributes |= VAR_ATTR_NO_VALUE;
	}
	var->attributes |= VAR_ATTR_EXPORTED;
	return (EXIT_SUCCESS);
}

static int	handle_assignment(
	t_context *ctx,
	t_parsed_variable_assignment result
)
{
	t_variable	*var;
	char		*new_value;

	var = getvar(ctx, result.name);
	if (var == NULL || result.operation == OPERATION_SET)
	{
		setvar(ctx, result.name, result.value, 1);
		var = getvar(ctx, result.name);
		var->attributes |= VAR_ATTR_EXPORTED;
		return (EXIT_SUCCESS);
	}
	if (result.operation == OPERATION_APPEND)
	{
		new_value = ft_strjoin(var->value, result.value);
		if (new_value == NULL)
			return (EXIT_FAILURE);
		setvar(ctx, result.name, new_value, 1);
	}
	return (EXIT_SUCCESS);
}

static int	process_parse_result(
	t_context *ctx,
	char *arg,
	t_assignment_parse_status status,
	t_parsed_variable_assignment result
)
{
	if (status == ASSIGN_PARSE_IGNORE)
		return (EXIT_SUCCESS);
	if (status == ASSIGN_PARSE_INVALID_IDENTIFIER)
	{
		print_quoted_error_builtin(ctx, "export", arg, ERR_IDENTIFIER);
		return (EXIT_FAILURE);
	}
	if (status == ASSIGN_PARSE_ONLY_IDENTIFIER)
		return (handle_only_identifier(ctx, result));
	return (handle_assignment(ctx, result));
}

int	export_each_arg(t_context *ctx, char *arg)
{
	int								handler_status;
	t_assignment_parse_status		parse_status;
	t_parsed_variable_assignment	result;

	parse_status = parse_variable_assignment(&result, arg);
	handler_status = process_parse_result(ctx, arg, parse_status, result);
	free(result.name);
	free(result.value);
	if (handler_status == EXIT_FAILURE
		|| parse_status == ASSIGN_PARSE_INTERNAL_ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
