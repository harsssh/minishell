/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:15:01 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 22:36:31 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins_internal.h"
#include "libft.h"
#include "variables.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void	print_env(void *data)
{
	t_variable	*var;

	var = (t_variable *)data;
	if (var->attributes & VAR_ATTR_EXPORTED
		&& !(var->attributes & VAR_ATTR_NO_VALUE))
		ft_putendl_fd((char *)var->envstr, STDOUT_FILENO);
}

int	builtins_env(t_context *ctx, const char **args)
{
	if (*args != NULL)
	{
		print_simple_error(ctx, "env", ERR_NOT_IMPL);
		return (EXIT_FAILURE);
	}
	errno = 0;
	ft_list_iter(ctx->variables, print_env);
	if (errno)
	{
		print_simple_error(ctx, "env", ERR_STDOUT);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
