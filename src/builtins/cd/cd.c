/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:53:09 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/17 17:10:47 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins/builtins_internal.h"
#include "cd_internal.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

int	builtins_cd(t_context *ctx, const char **args)
{
	const char	*dirname;

	args = ignore_options(args);
	if (*args == NULL || ft_strcmp(*args, "-") == 0)
	{
		print_simple_error(ctx, "cd", ERR_NOT_IMPL);
		return (EXIT_FAILURE);
	}
	dirname = args[0];
	if (change_directory(ctx, dirname) == 0)
		return (bindpwd(ctx));
	perror_verbose(ctx, "cd", dirname);
	return (EXIT_FAILURE);
}
