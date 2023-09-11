/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:52:07 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 19:17:32 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include <errno.h>
#include <stdlib.h>

static void	variable_destroy(void *data)
{
	t_variable	*var;

	var = data;
	free(var->name);
	free(var->value);
	free(var->envstr);
	free(var);
}

static bool	exclude_func(void *data, void *ref)
{
	t_variable	*var;
	char		*name;

	var = data;
	name = ref;
	return (ft_strcmp(var->name, name) == 0);
}

int	unsetvar(t_context *ctx, char *name)
{
	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	ft_list_remove_if(ctx->variables, name, exclude_func, variable_destroy);
	return (0);
}
