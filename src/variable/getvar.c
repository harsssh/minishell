/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 19:14:49 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variable.h"

static int	find_func(void *data, void *ref)
{
	return (ft_strcmp(((t_variable *)data)->name, (char *)ref));
}

t_variable	*getvar(t_context *ctx, char *name)
{
	t_variable	*var;

	var = ft_list_find(ctx->variables, name, find_func);
	return (var);
}
