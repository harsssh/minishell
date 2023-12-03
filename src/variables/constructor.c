/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:11:50 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/21 00:11:52 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include "variables_internal.h"
#include <stdlib.h>

t_variable	*variable_create(const char *name, const char *value)
{
	t_variable	*var;

	var = ft_xmalloc(sizeof(t_variable));
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

void	*variable_copy(void *data)
{
	t_variable	*var;
	t_variable	*new;

	var = (t_variable *)data;
	new = variable_create(ft_strdup(var->name), ft_strdup(var->value));
	if (new == NULL || new->name == NULL || new->value == NULL)
	{
		variable_destroy(new);
		return (NULL);
	}
	new->envstr = ft_strdup(var->envstr);
	if (new->envstr == NULL)
	{
		variable_destroy(new);
		return (NULL);
	}
	new->attributes = var->attributes;
	return ((void *)new);
}
