/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:35:22 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/21 00:10:37 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_internal.h"
#include <stdlib.h>

static t_ast_handler	get_ast_handler(t_ast_node_type type)
{
	if (type == N_COMMAND)
		return (handle_command);
	else if (type == N_AND || type == N_OR)
		return (handle_and_or);
	else if (type == N_PIPE)
		return (handle_pipeline);
	else
		return (NULL);
}

int	execute_ast_impl(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	t_ast_handler	handler;

	handler = get_ast_handler(ast->type);
	if (handler == NULL)
		return (EXIT_FAILURE);
	return (handler(ctx, info, ast));
}

int	execute_ast(t_context *ctx, t_ast_node *ast)
{
	t_pipeline_info	*info;
	int				ret;

	info = new_pipeline_info();
	if (info == NULL)
		return (EXIT_FAILURE);
	ret = execute_ast_impl(ctx, info, ast);
	destroy_pipeline_info(info);
	return (ret);
}
