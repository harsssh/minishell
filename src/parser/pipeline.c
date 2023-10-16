/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:06:55 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 21:47:13 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"

static void	*destroy_and_return_null(t_ast_node *node)
{
	destroy_node(node);
	return (NULL);
}

t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*node;
	t_ast_node	*rhs;

	node = parse_command(parser);
	while (!is_eof(parser) && node != NULL)
	{
		if (consume_token(parser, TK_PIPE))
		{
			rhs = parse_command(parser);
			if (rhs == NULL)
				return (destroy_and_return_null(node));
			node = new_ast_node(N_PIPE, node, rhs);
			if (node == NULL)
				return (destroy_and_return_null(rhs));
			continue ;
		}
		break ;
	}
	return (node);
}
