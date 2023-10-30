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

// name==NULL				: do nothing
// var==NULL, value=NULL	: create new variable with empty value
// var==NULL, value!=NULL	: create new variable with value
// var!=NULL, value=NULL	: do nothing
// var!=NULL, value!=NULL	: update variable with value
int	exportvar(t_context *ctx, const char *name, const char *value)
{
	t_variable	*var;

	if (name == NULL)
		return (EXIT_SUCCESS);
	var = getvar(ctx, name);
	if (var == NULL && value == NULL)
	{
		if (setvar(ctx, name, "", 1) == -1)
			return (EXIT_FAILURE);
		var = getvar(ctx, name);
		var->attributes |= VAR_ATTR_NO_VALUE;
	}
	else if (value != NULL)
	{
		if (setvar(ctx, name, value, 1) == -1)
			return (EXIT_FAILURE);
		var = getvar(ctx, name);
	}
	var->attributes |= VAR_ATTR_EXPORTED;
	return (EXIT_SUCCESS);
}
