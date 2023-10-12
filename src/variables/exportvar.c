/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 04:36:35 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/13 04:36:37 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include <stdlib.h>

// TODO: error handling when `getvar` or `setvar` fails
// if variable already exists and `name == NULL`, only set attributes,
// otherwise set appropriate value and attributes
int	exportvar(t_context *ctx, const char *name, const char *value)
{
	t_variable	*var;

	var = getvar(ctx, name);
	if (var == NULL && value == NULL)
	{
		setvar(ctx, name, "", 1);
		var = getvar(ctx, name);
		var->attributes |= VAR_ATTR_NO_VALUE;
	}
	else if (value != NULL)
	{
		setvar(ctx, name, value, 1);
		var = getvar(ctx, name);
	}
	var->attributes |= VAR_ATTR_EXPORTED;
	return (EXIT_SUCCESS);
}
