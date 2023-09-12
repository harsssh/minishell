/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:35:22 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/12 18:47:59 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <unistd.h>

static int	execute_ast_impl(t_context *ctx, t_ast_node *ast,
	int fd_in, int fd_out)
{
    (void)ctx;
    (void)ast;
    (void)fd_in;
    (void)fd_out;
	return (0);
}

int	execute_ast(t_context *ctx, t_ast_node *ast)
{
	return (execute_ast_impl(ctx, ast, STDIN_FILENO, STDOUT_FILENO));
}
