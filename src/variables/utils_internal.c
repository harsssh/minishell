/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:46 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 20:11:00 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include "variables_internal.h"
#include <stdlib.h>

char	*make_envstr(const char *name, const char *value)
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

void	variable_destroy(void *data)
{
	t_variable	*var;

	var = data;
	free((void *)var->name);
	free((void *)var->value);
	free((void *)var->envstr);
	free(var);
}

int	add_new_variable(t_context *ctx, const char *name, const char *value)
{
	t_variable	*new;

	name = ft_strdup(name);
	if (name == NULL)
		return (-1);
	value = ft_strdup(value);
	if (value == NULL)
	{
		free((void *)name);
		return (-1);
	}
	new = variable_create(name, value);
	if (new == NULL)
		return (-1);
	ft_list_push_back(ctx->variables, new);
	return (0);
}

int	update_variable(t_variable *var, const char *value)
{
	t_variable	tmp;

	tmp.value = ft_strdup(value);
	tmp.envstr = make_envstr(var->name, value);
	if (tmp.value == NULL || tmp.envstr == NULL)
	{
		free((void *)tmp.value);
		free((void *)tmp.envstr);
		return (-1);
	}
	free((void *)var->value);
	free((void *)var->envstr);
	var->value = tmp.value;
	var->envstr = tmp.envstr;
	var->attributes &= ~VAR_ATTR_NO_VALUE;
	return (0);
}
