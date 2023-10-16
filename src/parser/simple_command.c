/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:10:38 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 21:34:37 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_list.h"
#include "parser_internal.h"
#include "token.h"
#include <stdlib.h>

static void	*destroy_and_return_null(t_ast_node *node, t_list *list)
{
	destroy_node(node);
	ft_list_destroy(list, (void *)destroy_redirect);
	return (NULL);
}

// io_redirect+ ( 'WORD' cmd_suffix? )?
static t_ast_node	*parse_simple_command_helper(t_parser *parser)
{
	t_list		*redirects;
	t_ast_node	*node;

	redirects = parse_redirects(parser);
	if (redirects == NULL)
		return (NULL);
	if (peek_token(parser, TK_EOF))
		node = new_ast_node(N_COMMAND, NULL, NULL);
	else
		node = parse_word_cmd_suffix(parser);
	if (node == NULL)
		return (destroy_and_return_null(node, redirects));
	while (node->redirects != NULL && node->redirects->size != 0)
	{
		if (!ft_list_push_back(redirects, ft_list_pop_front(node->redirects)))
			return (destroy_and_return_null(node, redirects));
	}
	ft_list_destroy(node->redirects, (void *)destroy_redirect);
	set_node_redirects(node, redirects);
	return (node);
}

t_ast_node	*parse_simple_command(t_parser *parser)
{
	if (peek_redirect(parser))
		return (parse_simple_command_helper(parser));
	if (peek_token(parser, TK_WORD))
		return (parse_word_cmd_suffix(parser));
	return (NULL);
}
