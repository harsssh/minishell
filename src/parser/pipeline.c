/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:06:55 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/22 17:53:53 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"

t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*node;

	node = parse_simple_command(parser);
	while (!is_eof(parser) && node != NULL)
	{
		if (consume_token(parser, TK_PIPE))
			node = new_ast_node(N_PIPE, node, parse_simple_command(parser));
		else
			break ;
	}
	return (node);
}
