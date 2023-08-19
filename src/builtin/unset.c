/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 06:55:08 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/17 06:55:09 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_internal.h"
#include "variable.h"
#include <stdlib.h>

int	builtin_unset(t_context *ctx, char **args)
{
	args = ignore_options(args);
	while (*args != NULL)
	{
		unsetvar(ctx, *args);
		++args;
	}
	return (EXIT_SUCCESS);
}
