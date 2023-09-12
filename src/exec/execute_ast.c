/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:35:22 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/12 18:50:27 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_internal.h"
#include <unistd.h>

static int	execute_ast_impl(t_context *ctx, t_ast_node *ast,
	int fd_in, int fd_out)
{
	t_ast_handler	handler;

	handler = get_ast_handler(ast->type);
	return (handler(ctx, ast, fd_in, fd_out));
}

int	execute_ast(t_context *ctx, t_ast_node *ast)
{
	return (execute_ast_impl(ctx, ast, STDIN_FILENO, STDOUT_FILENO));
}
