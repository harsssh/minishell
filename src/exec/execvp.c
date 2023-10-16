/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:07:18 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 02:18:38 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_string.h"
#include "utils.h"
#include "variables.h"
#include <stdlib.h>
#include <unistd.h>

// `file` is a command name
static char	*try_each_path(char **path_list, const char *file)
{
	char	**cur;
	char	*cmd_path;

	cmd_path = NULL;
	cur = path_list;
	while (*cur != NULL)
	{
		cmd_path = join_path(*cur, (char *)file);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, R_OK | X_OK) == 0
			&& !is_existing_directory(cmd_path))
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		++cur;
	}
	return (cmd_path);
}

static char	*find_command_path(t_context *ctx, const char *file)
{
	t_variable	*var;
	char		**path_list;
	char		*cmd_path;

	if (file == NULL || *file == '\0')
		return (NULL);
	if (ft_strchr(file, '/') != NULL)
		return (ft_strdup(file));
	var = getvar(ctx, "PATH");
	if (var == NULL)
		return (NULL);
	path_list = ft_split(var->value, ':');
	if (path_list == NULL)
		return (NULL);
	cmd_path = try_each_path(path_list, file);
	destroy_string_array(path_list);
	return (cmd_path);
}

static void	print_error_and_exit(t_context *ctx, char **argv,
	const char *msg, int status)
{
	print_simple_error(ctx, argv[0], msg);
	exit(status);
}

/**
 * Note: `execve` fails with ENOENT (usually), if the command is a directory.
 * Make sure to specifically check for EISDIR to accurately handle the case.
 *
 * This function never returns.
 */
void	internal_execvp(t_context *ctx, t_list *arg_list)
{
	char	*cmd_path;
	char	**argv;
	char	**envp;

	argv = list_to_string_array(arg_list, NULL);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	cmd_path = find_command_path(ctx, argv[0]);
	if (cmd_path == NULL)
		print_error_and_exit(ctx, argv, ERR_CMD_NOT_FOUND, EXIT_CMD_NOT_FOUND);
	if (is_existing_directory(cmd_path))
		print_error_and_exit(ctx, argv, strerror(EISDIR), EXIT_OTHER_ERR);
	envp = get_environ(ctx);
	if (envp == NULL)
		exit(EXIT_FAILURE);
	errno = 0;
	if (execve(cmd_path, argv, envp) == -1)
	{
		print_simple_error(ctx, argv[0], strerror(errno));
		if (errno == ENOENT)
			exit(EXIT_CMD_NOT_FOUND);
		exit(EXIT_OTHER_ERR);
	}
}
