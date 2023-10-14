/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/14 22:16:25 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "builtins.h"
#include "context.h"
#include "exec_internal.h"
#include "ft_list.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static int	call_builtin_func(t_context *ctx, t_builtin_func func,
		t_list *argv_list)
{
	t_list	args_list;
	char	**args;
	int		ret;

	args_list = *argv_list;
	args_list.head = args_list.head->next;
	--args_list.size;
	args = list_to_string_array(&args_list, NULL);
	if (args == NULL)
		return (EXIT_FAILURE);
	ret = func(ctx, (const char **)args);
	destroy_string_array(args);
	return (ret);
}

/**
 * Note: If a directory is passed, `execve` fails with ENOENT (usually).
 * Make sure to specifically check for EISDIR to accurately handle the case.
 */
static int	execvp_with_error(t_context *ctx, t_list *argv_list)
{
	char	*command;

	errno = 0;
	internal_execvp(ctx, argv_list);
	command = (char *)argv_list->head->data;
	if (is_existing_directory(command))
		print_simple_error(ctx, command, strerror(EISDIR));
	else
		print_simple_error(ctx, command, strerror(errno));
	if (errno == ENOENT)
		return (EXIT_CMD_NOT_FOUND);
	return (EXIT_OTHER_ERR);
}

// If `argv` is NULL, it indicates a situation like "> file",
// which means there is no command to execute, so we exit with EXIT_SUCCESS.
static int	execute_command_in_child(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast, t_builtin_func func)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_simple_error(ctx, "fork", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (configure_io(ctx, info, ast->redirects) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (func != NULL)
			exit(call_builtin_func(ctx, func, ast->argv));
		if (ast->argv == NULL)
			exit(EXIT_SUCCESS);
		exit(execvp_with_error(ctx, ast->argv));
	}
	info->last_command_pid = pid;
	if (!is_in_pipeline(info))
		wait_children_and_set_exit_status(ctx, pid);
	return (EXIT_SUCCESS);
}

static int	execute_builtin(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast, t_builtin_func func)
{
	int	saved_stdin_fd;
	int	saved_stdout_fd;

	saved_stdin_fd = dup(STDIN_FILENO);
	saved_stdout_fd = dup(STDOUT_FILENO);
	if (configure_io(ctx, info, ast->redirects) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ctx->last_exit_status = call_builtin_func(ctx, func, ast->argv);
	dup2(saved_stdin_fd, STDIN_FILENO);
	dup2(saved_stdout_fd, STDOUT_FILENO);
	close(saved_stdin_fd);
	close(saved_stdout_fd);
	return (EXIT_SUCCESS);
}

int	handle_command(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	t_builtin_func	func;

	if (ast->argv != NULL)
		func = get_builtin_func((char *)ast->argv->head->data);
	else
		func = NULL;
	if (func != NULL && !is_in_pipeline(info))
		return (execute_builtin(ctx, info, ast, func));
	else
		return (execute_command_in_child(ctx, info, ast, func));
}
