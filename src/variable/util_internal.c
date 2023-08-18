/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:46 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 19:14:47 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variable.h"
#include "variable_internal.h"
#include <stdlib.h>

static char	*make_envstr(char *name, char *value)
{
	char	*envstr;
	char	*tmp;

	envstr = ft_strjoin(name, "=");
	if (envstr == NULL)
		return (NULL);
	tmp = envstr;
	envstr = ft_strjoin(envstr, value);
	free(tmp);
	if (envstr == NULL)
		return (NULL);
	return (envstr);
}

t_variable	*variable_create(char *name, char *value)
{
	t_variable	*var;

	var = malloc(sizeof(t_variable));
	if (var == NULL)
		return (NULL);
	var->name = name;
	var->value = value;
	var->envstr = make_envstr(name, value);
	if (var->envstr == NULL)
	{
		free(var);
		return (NULL);
	}
	var->attributes = 0;
	return (var);
}

int	add_new_variable(t_context *ctx, char *name, char *value)
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

int	update_variable(t_variable *var, char *value)
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
	var->attributes &= ~VAR_ATTR_NO_VALUE;
	return (0);
}
