/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:32:03 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/30 17:04:22 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# include "context.h"

typedef enum e_variable_attribute
{
	VAR_ATTR_EXPORTED = (1 << 0),
	VAR_ATTR_NO_VALUE = (1 << 1),
}	t_variable_attribute;

typedef struct s_variable
{
	const char				*name;
	const char				*value;
	const char				*envstr;
	int						attributes;
}	t_variable;

typedef enum e_operation_type
{
	OP_SET,
	OP_APPEND,
}	t_operation_type;

typedef enum e_parse_status
{
	ASSIGN_PARSE_SUCCESS,
	ASSIGN_PARSE_ONLY_IDENTIFIER,
	ASSIGN_PARSE_INVALID_IDENTIFIER,
	ASSIGN_PARSE_INTERNAL_ERROR,
}	t_parse_status;

typedef struct s_parsed_assignment
{
	char					*name;
	char					*value;
	t_operation_type		operation;
}							t_parsed_assignment;

t_variable		*getvar(t_context *ctx, const char *name);
int				setvar(t_context *ctx, const char *name,
					const char *value, int overwrite);
int				unsetvar(t_context *ctx, const char *name);
int				exportvar(t_context *ctx, const char *name,
					const char *value);

char			**get_environ(t_context *ctx);
t_parse_status	parse_assignment(
					t_parsed_assignment *result, const char *str);

#endif
