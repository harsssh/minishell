/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_each_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:18:02 by kemizuki          #+#    #+#             */
/*   Updated: 2023/12/03 19:23:35 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins_internal.h"
#include "export_internal.h"
#include "libft.h"
#include "variables.h"
#include <stdlib.h>

static int	handle_assignment(
		t_context *ctx,
		t_parsed_assignment result)
{
	t_variable	*var;
	char		*new_value;
	int			ret;

	var = getvar(ctx, result.name);
	if (var == NULL || result.operation == OP_SET)
		return (exportvar(ctx, result.name, result.value));
	if (result.operation == OP_APPEND)
	{
		new_value = ft_strjoin(var->value, result.value);
		if (new_value == NULL)
			return (EXIT_FAILURE);
		ret = exportvar(ctx, result.name, new_value);
		free(new_value);
		return (ret);
	}
	return (EXIT_SUCCESS);
}

static int	process_parse_result(
		t_context *ctx,
		const char *arg,
		t_parse_status status,
		t_parsed_assignment result)
{
	if (status == ASSIGN_PARSE_IGNORE)
		return (EXIT_SUCCESS);
	if (status == ASSIGN_PARSE_INVALID_IDENTIFIER)
	{
		print_quoted_error(ctx, "export", arg, ERR_IDENTIFIER);
		return (EXIT_FAILURE);
	}
	if (status == ASSIGN_PARSE_ONLY_IDENTIFIER)
		return (exportvar(ctx, result.name, NULL));
	return (handle_assignment(ctx, result));
}

int	export_each_arg(t_context *ctx, const char *arg)
{
	int					handler_status;
	t_parse_status		parse_status;
	t_parsed_assignment	result;

	parse_status = parse_assignment(&result, arg);
	handler_status = process_parse_result(ctx, arg, parse_status, result);
	free(result.name);
	free(result.value);
	if (handler_status == EXIT_FAILURE
		|| parse_status == ASSIGN_PARSE_INTERNAL_ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
