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

char	*make_envstr(char *name, char *value)
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
