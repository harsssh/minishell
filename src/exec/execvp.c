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

static int execute_from_path(char **path_array, const char *file, char *const *argv)
{
}

int	internal_execvp(t_context *ctx, const char *file, char *const *argv)
{
	t_variable	*var;
	char		**envp;
	char		**path_array;

	if (file == NULL || *file == '\0')
		return (-1);
	envp = get_environ(ctx);
	if (envp == NULL)
		return (-1);
	if (!is_absolute_path(file))
		return execve(file, argv, envp);
	var = getvar(ctx, "PATH");
	if (var == NULL)
		return execve(file, argv, envp);
	path_array = ft_split(var->value, ':');
	if (path_array == NULL)
		destroy_string_array(envp);
	return (-1);
}
