/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:58:05 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/17 19:15:31 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_internal.h"
#include "utils.h"
#include <stdlib.h>

int	handle_subshell(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
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
		ctx->is_interactive = false;
		configure_io(ctx, info, ast->redirects);
		execute_ast(ctx, ast->left);
		exit(ctx->last_exit_status);
	}
	if (!is_in_pipeline(info))
		wait_children_and_set_exit_status(ctx, pid);
	return (EXIT_SUCCESS);
}
