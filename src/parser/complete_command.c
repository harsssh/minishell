/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:08:42 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/19 17:08:43 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"

// complete_command ::= and_or ( separator_op and_or )* separator_op?
t_ast_node	*parse_complete_command(t_parser *parser)
{
	t_ast_node	*node;
	t_ast_node	*lhs;
	t_ast_node	*rhs;

	node = parse_and_or(parser);
	while (!is_eof(parser) && node != NULL)
	{
		if (!consume_token(parser, TK_SEMICOLON) || peek_token(parser, TK_EOF))
			break ;
		rhs = parse_and_or(parser);
		if (rhs == NULL)
			return (destroy_nodes_and_return_null(node, NULL));
		lhs = node;
		node = new_ast_node(N_SEMICOLON, lhs, rhs);
		if (node == NULL)
			return (destroy_nodes_and_return_null(lhs, rhs));
	}
	return (node);
}
