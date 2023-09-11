/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:53:09 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/20 01:53:10 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins/builtins_internal.h"
#include "cd_internal.h"
#include "variables.h"
#include <stdlib.h>

static int	bindpwd(t_context *ctx)
{
	char	*dirname;
	int		result;

	dirname = get_working_directory(ctx, "cd");
	if (dirname == NULL)
		return (EXIT_FAILURE);
	if (setvar(ctx, "PWD", dirname, 1) == 0)
		result = EXIT_SUCCESS;
	else
		result = EXIT_FAILURE;
	free(dirname);
	return (result);
}

int	builtin_cd(t_context *ctx, char **args)
{
	char	*dirname;

	if (*args == NULL)
	{
		print_simple_error_builtin(ctx, "cd", ERR_NOT_IMPL);
		return (EXIT_FAILURE);
	}
	args = ignore_options(args);
	dirname = args[0];
	if (change_directory(ctx, dirname) == 0)
		return (bindpwd(ctx));
	perror_builtin(ctx, "cd", dirname);
	return (EXIT_FAILURE);
}
