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

static void	*parse_command_helper(t_ast_node *node1, t_ast_node *node2)
{
	destroy_node(node1);
	destroy_node(node2);
	return (NULL);
}

t_ast_node	*parse_command(t_parser *parser)
{
	t_ast_node	*node;
	t_ast_node	*lhs;

	if (consume_token(parser, TK_LPAREN))
	{
		lhs = parse_and_or(parser);
		if (lhs == NULL)
			return (parse_command_helper(lhs, NULL));
		node = new_ast_node(N_SUBSHELL, lhs, NULL);
		if (node == NULL)
			return (parse_command_helper(lhs, node));
		if (!consume_token(parser, TK_RPAREN))
			return (parse_command_helper(node, NULL));
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
