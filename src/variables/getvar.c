/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 19:17:21 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include <stdbool.h>

static bool	find_func(void *data, void *ref)
{
	return (ft_strcmp(((t_variable *)data)->name, (char *)ref) == 0);
}

t_variable	*getvar(t_context *ctx, char *name)
{
	t_variable	*var;

	var = ft_list_find(ctx->variables, name, find_func);
	return (var);
}
