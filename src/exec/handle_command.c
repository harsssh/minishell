/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 21:31:15 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "context.h"
#include "exec_internal.h"
#include "builtins.h"
#include "ft_list.h"
#include "utils.h"
#include <stdlib.h>

static int call_builtin_func(t_context *ctx, t_list *argv_list, t_builtin_func func)
{
	char **argv;
	int ret;

	argv = list_to_string_array(argv_list, NULL);
	if (argv == NULL)
		return (EXIT_FAILURE);
	ret = func(ctx, argv);
	destroy_string_array(argv);
	return (ret);
}

static void execute_command_in_child(t_context *ctx, t_pipeline_info *info, t_ast_node *ast, t_builtin_func func)
{
	pid_t	pid;

 	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		configure_io(ast->redirects, info);
		if (func != NULL)
			exit(call_builtin_func(ctx, ast->argv, func));
		else
			internal_execvp(ctx, ast->argv);
		exit(EXIT_FAILURE);
	}
	push_child_pid_list(info, pid);
	if (!is_in_pipeline(info))
		wait_children(ctx, info->child_pid_list);
}

static void execute_builtin(t_context *ctx, t_pipeline_info *info, t_ast_node *ast, t_builtin_func func)
{

}

int	handle_command(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	t_builtin_func func;

	func = get_builtin_func((char *)ast->argv->head->data);
	if (func != NULL && !is_in_pipeline(info))
		execute_builtin(ctx, info, ast, func);
	else
		execute_command_in_child(ctx, info, ast, func);
	return (EXIT_SUCCESS);
}
