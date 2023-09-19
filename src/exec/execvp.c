/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:07:18 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/19 22:19:04 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_string.h"
#include "variables.h"
#include "utils.h"
#include <unistd.h>

int	internal_execvp(t_context *ctx, const char *file, char *const *argv)
{
	t_variable	*var;
	char		**envp;
	char		**path_array;

	envp = get_environ(ctx);
	if (envp == NULL)
		return (-1);
	var = getvar(ctx, "PATH");
	if (var == NULL)
	{
		execve(file, argv, envp);
		return (-1);
	}
	path_array = ft_split(var->value, ':');
	if (path_array == NULL)
		destroy_string_array(envp);
	return (0);
}
