/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:29 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/21 20:19:54 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>

int	handle_and_or(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	if (execute_ast_impl(ctx, info, ast->left) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_children_and_set_exit_status(ctx, info->last_command_pid);
	if ((ast->type == N_AND && ctx->last_exit_status == EXIT_SUCCESS)
		|| (ast->type == N_OR && ctx->last_exit_status != EXIT_SUCCESS))
	{
		if (execute_ast_impl(ctx, info, ast->right) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
