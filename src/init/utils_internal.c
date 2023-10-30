/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:09:51 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/30 01:10:32 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_internal.h"
#include "libft.h"
#include "variables.h"
#include <stdlib.h>

int	inherit_env(t_context *ctx, char **envp)
{
	char	*eq_ptr;

	while (*envp != NULL)
	{
		eq_ptr = ft_strchr(*envp, '=');
		if (eq_ptr != NULL)
		{
			*eq_ptr = '\0';
			if (exportvar(ctx, *envp, eq_ptr + 1) == -1)
				return (EXIT_FAILURE);
			*eq_ptr = '=';
		}
		++envp;
	}
	return (EXIT_SUCCESS);
}
