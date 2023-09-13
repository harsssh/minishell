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

static t_ast_handler get_ast_handler(t_ast_node_type type)
{
    // if (type == N_COMMAND)
    //     return handle_command;
    // else if (type == N_SEQUENCE)
    //     return handle_sequence;
    // else if (type == N_AND || type == N_OR)
    //     return handle_logical_operator;
    // else if (type == N_PIPE)
    //     return handle_pipe;
    // else if (type == N_REDIRECT_IN || type == N_REDIRECT_OUT 
    //     || type == N_REDIRECT_APPEND || type == N_REDIRECT_HERE_DOC)
    //     return handle_redirect;
    // else if (type == N_REDIRECT_HERE_DOC)
    //     return handle_redirect;
    // else
    //     return NULL;
    (void)type;
    return (NULL);
}

int	execute_ast(t_context *ctx, t_ast_node *ast)
{
	t_ast_handler handler;

	handler = get_ast_handler(ast->type);
	return (handler(ctx, ast, NULL, NULL));
}
