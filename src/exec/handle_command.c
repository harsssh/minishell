/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 19:02:38 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "context.h"
#include "exec_internal.h"
#include "builtins.h"
#include "ft_list.h"
#include <stdlib.h>

int	handle_command(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	pid_t	pid;
	t_builtin_func builtin_func;

	builtin_func = get_builtin_func((char *)ast->argv->head->data);
	if (builtin_func != NULL)
	{
		return EXIT_SUCCESS;
	}
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		configure_io(ast->redirects, info);
		internal_execvp(ctx, ast->argv);
		exit(EXIT_FAILURE);
	}
	push_child_pid_list(info, pid);
	if (!is_in_pipeline(info))
		wait_children(ctx, info->child_pid_list);
	return (EXIT_SUCCESS);
}
