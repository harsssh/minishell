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

#include "libft.h"
#include "variable.h"
#include "variable_internal.h"
#include <errno.h>
#include <stdlib.h>

static int	add_new_variable(t_context *ctx, char *name, char *value)
{
	t_variable	*new;

	name = ft_strdup(name);
	if (name == NULL)
		return (-1);
	value = ft_strdup(value);
	if (value == NULL)
	{
		free(name);
		return (-1);
	}
	new = variable_create(name, value);
	if (new == NULL)
		return (-1);
	ft_list_push_back(ctx->variables, new);
	return (0);
}

static int	update_variable(t_variable *var, char *value)
{
	t_variable	tmp;

	tmp.value = ft_strdup(value);
	tmp.envstr = make_envstr(var->name, value);
	if (tmp.value == NULL || tmp.envstr == NULL)
	{
		free(tmp.value);
		free(tmp.envstr);
		return (-1);
	}
	free(var->value);
	free(var->envstr);
	var->value = tmp.value;
	var->envstr = tmp.envstr;
	return (0);
}

int	setvar(t_context *ctx, char *name, char *value, int overwrite)
{
	t_variable	*var;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
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
