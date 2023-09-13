/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:32:03 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 19:27:05 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# include "context.h"

typedef enum e_variable_attribute {
	VAR_ATTR_EXPORTED = (1 << 0),
	VAR_ATTR_NO_VALUE = (1 << 1),
}	t_variable_attribute;

typedef struct s_variable
{
	char	*name;
	char	*value;
	char	*envstr;
	int		attributes;
}			t_variable;

typedef enum e_operation_type {
	OPERATION_SET,
	OPERATION_APPEND,
}	t_operation_type;

typedef enum e_assignment_parse_status {
	ASSIGN_PARSE_SUCCESS,
	ASSIGN_PARSE_IGNORE,
	ASSIGN_PARSE_ONLY_IDENTIFIER,
	ASSIGN_PARSE_INVALID_IDENTIFIER,
	ASSIGN_PARSE_INTERNAL_ERROR,
}	t_assignment_parse_status;

typedef struct s_parsed_variable_assignment {
	char				*name;
	char				*value;
	t_operation_type	operation;
}	t_parsed_variable_assignment;

t_variable					*getvar(t_context *ctx, char *name);
int							setvar(t_context *ctx, char *name, char *value,
								int overwrite);
int							unsetvar(t_context *ctx, char *name);

char 						**get_environ(t_context *ctx);
t_assignment_parse_status	parse_variable_assignment(
								t_parsed_variable_assignment *result,
								char *str);

#endif
