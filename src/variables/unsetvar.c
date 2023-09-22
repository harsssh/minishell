/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:52:07 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/23 04:43:44 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include "variables_internal.h"
#include <errno.h>

static bool	exclude_func(void *data, void *ref)
{
	t_variable	*var;
	char		*name;

	var = data;
	name = ref;
	return (ft_strcmp(var->name, name) == 0);
}

int	unsetvar(t_context *ctx, const char *name)
{
	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	ft_list_remove_if(ctx->variables, (void *)name,
		exclude_func, variable_destroy);
	return (0);
}
