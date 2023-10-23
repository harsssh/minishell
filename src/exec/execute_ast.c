/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:35:22 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/17 18:45:15 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_internal.h"
#include <stdlib.h>

int	execute_ast_impl(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	if (ast == NULL)
		return (EXIT_SUCCESS);
	if (ast->type == N_COMMAND)
		return (handle_command(ctx, info, ast));
	else if (ast->type == N_AND || ast->type == N_OR)
		return (handle_and_or(ctx, info, ast));
	else if (ast->type == N_PIPE)
		return (handle_pipeline(ctx, info, ast));
	else if (ast->type == N_SUBSHELL)
		return (handle_subshell(ctx, info, ast));
	else if (ast->type == N_SEMICOLON)
		return (handle_semicolon(ctx, info, ast));
	return (EXIT_FAILURE);
}

int	execute_ast(t_context *ctx, t_ast_node *ast)
{
	t_pipeline_info	*info;
	int				ret;

	if (ast == NULL)
		return (EXIT_SUCCESS);
	info = new_pipeline_info();
	if (info == NULL)
		return (EXIT_FAILURE);
	ret = execute_ast_impl(ctx, info, ast);
	wait_children_and_set_exit_status(ctx, info->last_command_pid);
	destroy_pipeline_info(info);
	return (ret);
}
