/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:22:30 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 19:23:46 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include "variables_internal.h"
#include <stdlib.h>

static t_parse_status	parse_only_identifier(
		t_parsed_assignment *result,
		const char *str
)
{
	if (!is_valid_identifier(str))
		return (ASSIGN_PARSE_INVALID_IDENTIFIER);
	result->name = ft_strdup(str);
	if (result->name == NULL)
		return (ASSIGN_PARSE_INTERNAL_ERROR);
	return (ASSIGN_PARSE_ONLY_IDENTIFIER);
}

// `str` must contain '='.
static int	extract_pair(const char *str, char **name, char **value)
{
	char	*assignment_pos;
	char	*name_end;
	char	*value_start;

	assignment_pos = ft_strchr(str, '=');
	if (assignment_pos != str && assignment_pos[-1] == '+')
		name_end = assignment_pos - 1;
	else
		name_end = assignment_pos;
	value_start = assignment_pos + 1;
	*name = ft_substr(str, 0, name_end - str);
	if (*name == NULL)
		return (EXIT_FAILURE);
	*value = ft_strdup(value_start);
	if (*value == NULL)
	{
		free(*name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// `str` must contain '='.
// If `str` starts with '=' or '+=', it should return an error.
static t_parse_status	parse_operation(
		t_parsed_assignment *result,
		const char *str
)
{
	char	*assignment_pos;

	assignment_pos = ft_strchr(str, '=');
	if (assignment_pos == NULL)
		return (ASSIGN_PARSE_INTERNAL_ERROR);
	if (assignment_pos != str && assignment_pos[-1] == '+')
	{
		--assignment_pos;
		result->operation = OP_APPEND;
	}
	else
		result->operation = OP_SET;
	if (assignment_pos == str)
		return (ASSIGN_PARSE_INVALID_IDENTIFIER);
	return (ASSIGN_PARSE_SUCCESS);
}

static t_parse_status	parse_pair(
		t_parsed_assignment *result,
		const char *str
)
{
	t_parse_status	status;

	status = ASSIGN_PARSE_SUCCESS;
	if (extract_pair(str, &result->name, &result->value) == EXIT_FAILURE)
		return (ASSIGN_PARSE_INTERNAL_ERROR);
	if (!is_valid_identifier(result->name))
		status = ASSIGN_PARSE_INVALID_IDENTIFIER;
	else if (ft_strcmp(result->name, "_") == 0)
		status = ASSIGN_PARSE_IGNORE;
	if (status != ASSIGN_PARSE_SUCCESS)
	{
		free(result->name);
		free(result->value);
		result->name = NULL;
		result->value = NULL;
	}
	return (status);
}

t_parse_status	parse_assignment(
		t_parsed_assignment *result,
		const char *str
)
{
	t_parse_status	status;

	result->name = NULL;
	result->value = NULL;
	if (ft_strchr(str, '=') == NULL)
		return (parse_only_identifier(result, str));
	status = parse_operation(result, str);
	if (status != ASSIGN_PARSE_SUCCESS)
		return (status);
	return (parse_pair(result, str));
}
