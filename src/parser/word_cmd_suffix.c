/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_cmd_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:31 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/20 22:00:31 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include <stdlib.h>

char	*parse_word(t_parser *parser)
{
	if (!peek_token(parser, TK_WORD))
		return (NULL);
	return (get_token_literal(get_cur_token(parser)));
}

t_ast_node	*parse_word_cmd_suffix(t_parser *parser)
{
	t_ast_node	*node;
	char		*command_name;

	node = new_ast_node(N_COMMAND, NULL, NULL);
	if (node == NULL)
		return (NULL);
	command_name = parse_word(parser);
	if (command_name == NULL
		|| add_node_argv(node, command_name)
		|| parse_cmd_suffix(parser, node))
	{
		destroy_node(node);
		free(command_name);
		return (NULL);
	}
	return (node);
}
