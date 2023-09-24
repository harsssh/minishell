/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/23 06:27:55 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "builtins.h"
#include "context.h"
#include "exec_internal.h"
#include "ft_list.h"
#include "utils.h"
#include <stdlib.h>

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

static void	execute_command_in_child(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast, t_builtin_func func)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		configure_io(info, ast->redirects);
		if (func != NULL)
			exit(call_builtin_func(ctx, func, ast->argv));
		else
			internal_execvp(ctx, ast->argv);
		exit(EXIT_FAILURE);
	}
	info->last_command_pid = pid;
	if (!is_in_pipeline(info))
		wait_children_and_set_exit_status(ctx, pid);
}

static void	execute_builtin(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast, t_builtin_func func)
{
	int	saved_stdin_fd;
	int	saved_stdout_fd;

	saved_stdin_fd = dup(STDIN_FILENO);
	saved_stdout_fd = dup(STDOUT_FILENO);
	configure_io(info, ast->redirects);
	ctx->last_exit_status = call_builtin_func(ctx, func, ast->argv);
	dup2(saved_stdin_fd, STDIN_FILENO);
	dup2(saved_stdout_fd, STDOUT_FILENO);
	close(saved_stdin_fd);
	close(saved_stdout_fd);
}

int	handle_command(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	t_builtin_func	func;

	func = get_builtin_func((char *)ast->argv->head->data);
	if (func != NULL && !is_in_pipeline(info))
		execute_builtin(ctx, info, ast, func);
	else
		execute_command_in_child(ctx, info, ast, func);
	return (EXIT_SUCCESS);
}
