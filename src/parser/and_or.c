/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:04:42 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/19 17:06:36 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"

t_ast_node	*parse_and_or(t_parser *parser)
{
	t_ast_node	*node;

	node = parse_pipeline(parser);
	while (!is_eof(parser) && node != NULL)
	{
		if (consume_token(parser, TK_AND))
			node = new_ast_node(N_AND, node, parse_pipeline(parser));
		else if (consume_token(parser, TK_OR))
			node = new_ast_node(N_OR, node, parse_pipeline(parser));
		else
			break ;
	}
	return (node);
}
