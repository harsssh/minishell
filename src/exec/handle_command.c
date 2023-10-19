/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 02:02:08 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "builtins.h"
#include "context.h"
#include "exec_internal.h"
#include "ft_list.h"
#include "sig.h"
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

// This function never returns.
static void	child_routine(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast, t_builtin_func func)
{
	set_child_exec_sig_handlers();
	ctx->is_login = false;
	ctx->is_interactive = false;
	if (configure_io(ctx, info, ast->redirects) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (func != NULL)
		exit(call_builtin_func(ctx, func, ast->argv));
	if (ast->argv == NULL)
		exit(EXIT_SUCCESS);
	internal_execvp(ctx, ast->argv);
	exit(EXIT_FAILURE);
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
		child_routine(ctx, info, ast, func);
	set_shell_exec_sig_handlers();
	if (info->fd_out == STDOUT_FILENO)
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
	{
		close(saved_stdin_fd);
		close(saved_stdout_fd);
		return (EXIT_FAILURE);
	}
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
