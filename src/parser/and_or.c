/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:04:42 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 21:47:17 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include <stdlib.h>

static int	parse_and(t_parser *parser, t_ast_node **node)
{
	t_ast_node	*rhs;

	rhs = parse_pipeline(parser);
	if (rhs == NULL)
	{
		destroy_node(*node);
		return (EXIT_FAILURE);
	}
	*node = new_ast_node(N_AND, *node, rhs);
	if (*node == NULL)
	{
		destroy_node(rhs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	parse_or(t_parser *parser, t_ast_node **node)
{
	t_ast_node	*rhs;

	rhs = parse_pipeline(parser);
	if (rhs == NULL)
	{
		destroy_node(*node);
		return (EXIT_FAILURE);
	}
	*node = new_ast_node(N_OR, *node, rhs);
	if (*node == NULL)
	{
		destroy_node(rhs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_ast_node	*parse_and_or(t_parser *parser)
{
	t_ast_node	*node;

	node = parse_pipeline(parser);
	while (!is_eof(parser) && node != NULL)
	{
		if (consume_token(parser, TK_AND))
		{
			if (parse_and(parser, &node))
				return (NULL);
			continue ;
		}
		else if (consume_token(parser, TK_OR))
		{
			if (parse_or(parser, &node))
				return (NULL);
			continue ;
		}
		break ;
	}
	return (node);
}
