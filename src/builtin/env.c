/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:15:01 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/17 02:15:02 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_internal.h"
#include "libft.h"
#include "variable.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void	print_env(void *data)
{
	t_variable	*var;

	var = (t_variable *)data;
	if (var->attributes & VAR_ATTR_EXPORTED)
		ft_putendl_fd(var->envstr, STDOUT_FILENO);
}

int	builtin_env(t_context *ctx, char **args)
{
	if (*args != NULL)
	{
		builtin_not_implemented(ctx, "env");
		return (EXIT_FAILURE);
	}
	errno = 0;
	ft_list_iter(ctx->variables, print_env);
	if (errno)
	{
		builtin_stdout_error(ctx, "env");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
