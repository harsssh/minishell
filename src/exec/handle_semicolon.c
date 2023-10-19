/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_semicolon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:02:50 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/19 18:02:52 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>

int	handle_semicolon(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	if (execute_ast_impl(ctx, info, ast->left) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_children_and_set_exit_status(ctx, info->last_command_pid);
	return (execute_ast_impl(ctx, info, ast->right));
}
