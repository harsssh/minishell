/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:35:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/12 18:35:21 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
#define EXEC_INTERNAL_H

#include "context.h"
#include "ast.h"

typedef struct s_pipe {
    int fd_in;
    int fd_out;
} t_pipe;

void new_pipe(t_pipe *p);

typedef int (*t_ast_handler)(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe);

int handle_command(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe);
int handle_sequence(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe);
int handle_logical_operator(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe);
int handle_pipe(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe);
int handle_redirect(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe);

#endif
