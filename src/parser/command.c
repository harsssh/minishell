/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:10:38 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/25 19:27:47 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_list.h"
#include "parser_internal.h"
#include "token.h"
#include <stdlib.h>

// io_redirect+ ( 'WORD' cmd_suffix? )?
static t_ast_node	*parse_simple_command_helper(t_parser *parser)
{
	t_list		*redirects;
	t_ast_node	*node;

	redirects = parse_redirects(parser);
	if (redirects == NULL)
		return (NULL);
	if (peek_token(parser, TK_WORD))
		node = parse_word_cmd_suffix(parser);
	else
		node = new_ast_node(N_COMMAND, NULL, NULL);
	set_node_redirects(node, redirects);
	return (node);
}

t_ast_node	*parse_simple_command(t_parser *parser)
{
	if (peek_redirect(parser))
		return (parse_simple_command_helper(parser));
	if (peek_token(parser, TK_WORD))
		return (parse_word_cmd_suffix(parser));
	if (peek_token(parser, TK_EOF))
		return (new_ast_node(N_COMMAND, NULL, NULL));
	return (NULL);
}
