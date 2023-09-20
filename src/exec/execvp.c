/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:07:18 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/20 20:25:54 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_string.h"
#include "utils.h"
#include "variables.h"
#include <stdlib.h>
#include <unistd.h>

// `file` must be a relative path
static char *try_each_path(char **path_list, const char *file)
{
	char **cur;
	char *cmd_path;

	cur = path_list;
	while (*cur != NULL)
	{
		cmd_path = join_path(*cur, (char *)file);
		++cur;
	}
	return (cmd_path);
}

static char	*find_command_path(t_context *ctx, const char *file)
{
	t_variable *var;
	char **path_list;
	cahr *cmd_path;

	if (file == NULL || *file == '\0')
		return NULL;
	if (is_absolute_path(file))
		return ft_strdup(file);
	var = getvar(ctx, "PATH");
	if (var == NULL)
		return NULL;
	path_list = ft_split(var->value, ':');
	if (path_list == NULL)
		return NULL;
	cmd_path = try_each_path(path_list, file);
	destroy_string_array(path_list);
	return (cmd_path);
}

int	internal_execvp(t_context *ctx, const char *file, char *const *argv)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = find_command_path(ctx, file);
	if (cmd_path == NULL)
		return (-1);
	envp = get_environ(ctx);
	if (envp == NULL)
	{
		free(cmd_path);
		return (-1);
	}
	return (execve(cmd_path, argv, envp));
}