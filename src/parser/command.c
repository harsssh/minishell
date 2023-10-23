/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:39:02 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 20:58:24 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"

t_ast_node	*parse_command(t_parser *parser)
{
	t_ast_node	*node;
	t_ast_node	*lhs;

	if (consume_token(parser, TK_LPAREN))
	{
		lhs = parse_complete_command(parser);
		if (lhs == NULL)
			return (destroy_nodes_and_return_null(lhs, NULL));
		node = new_ast_node(N_SUBSHELL, lhs, NULL);
		if (node == NULL)
			return (destroy_nodes_and_return_null(lhs, node));
		if (!consume_token(parser, TK_RPAREN))
			return (destroy_nodes_and_return_null(node, NULL));
		if (peek_redirect(parser))
		{
			node->redirects = parse_redirects(parser);
			if (node->redirects == NULL)
			{
				destroy_node(node);
				return (NULL);
			}
		}
		return (node);
	}
	return (parse_simple_command(parser));
}
