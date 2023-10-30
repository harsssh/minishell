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

static t_parse_status	only_identifier(
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

static int	extract_pair(const char *str, char **name, char **value)
{
	char	*offset;
	char	*name_end;
	char	*value_start;

	offset = ft_strchr(str, '=');
	if (offset[-1] == '+')
		name_end = offset - 1;
	else
		name_end = offset;
	value_start = offset + 1;
	*name = ft_substr(str, 0, name_end - str);
	if (*name == NULL)
		return (-1);
	*value = ft_strdup(value_start);
	if (*value == NULL)
	{
		free(*name);
		return (-1);
	}
	return (0);
}

// str != NULL
static t_parse_status	parse_operation(
		t_parsed_assignment *result,
		const char *str
)
{
	char	*offset;

	offset = ft_strchr(str, '=');
	if (offset == NULL)
		return (ASSIGN_PARSE_INTERNAL_ERROR);
	if (offset[-1] == '+')
	{
		if (offset == str + 1)
			return (ASSIGN_PARSE_INVALID_IDENTIFIER);
		result->operation = OP_APPEND;
	}
	else
		result->operation = OP_SET;
	return (ASSIGN_PARSE_SUCCESS);
}

static t_parse_status	parse_pair(
		t_parsed_assignment *result,
		const char *str
)
{
	t_parse_status	status;

	status = ASSIGN_PARSE_SUCCESS;
	if (extract_pair(str, &result->name, &result->value) == -1)
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
		return (only_identifier(result, str));
	status = parse_operation(result, str);
	if (status != ASSIGN_PARSE_SUCCESS)
		return (status);
	return (parse_pair(result, str));
}
