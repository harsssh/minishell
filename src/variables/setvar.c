/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:50 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 19:14:51 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "variables_internal.h"
#include <errno.h>

int	setvar(t_context *ctx, char *name, char *value, int overwrite)
{
	t_variable	*var;

	if (name == NULL || *name == '\0' || !is_valid_identifier(name))
	{
		errno = EINVAL;
		return (-1);
	}
	var = getvar(ctx, name);
	if (var == NULL)
		return (add_new_variable(ctx, name, value));
	if (overwrite)
		return (update_variable(var, value));
	return (0);
}
