/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:12:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/21 20:36:55 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "variables.h"
#include "variables_internal.h"

static bool	is_inheritable(void *data)
{
	t_variable	*var;

	var = (t_variable *)data;
	return ((var->attributes & VAR_ATTR_EXPORTED)
		&& !(var->attributes & VAR_ATTR_NO_VALUE));
}

// reuse `envstr` in variable
// `envstr` is NOT freed by variable destructor
static char	*get_envstr_from_variable(void *data)
{
	t_variable	*var;
	char		*envstr;

	var = (t_variable *)data;
	envstr = var->envstr;
	var->envstr = NULL;
	return (envstr);
}

char	**get_environ(t_context *ctx)
{
	t_list	*filtered;
	char	**envp;

	filtered = ft_list_filter(ctx->variables, is_inheritable, variable_copy,
			variable_destroy);
	if (filtered == NULL)
		return (NULL);
	envp = list_to_string_array(filtered, get_envstr_from_variable);
	ft_list_destroy(filtered, variable_destroy);
	return (envp);
}
