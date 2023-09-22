/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:10:38 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/20 21:56:55 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_list.h"
#include "parser_internal.h"
#include "token.h"
#include <stdlib.h>

static void	destroy_redirect_helper(void *data)
{
	destroy_redirect(data);
}

// io_redirect+ ( 'WORD' cmd_suffix? )?
static t_ast_node	*parse_simple_command_helper(t_parser *parser)
{
	t_list		*redirects;
	t_redirect	*redirect;
	t_ast_node	*node;

	redirects = ft_list_create();
	if (redirects == NULL)
		return (NULL);
	while (peek_redirect(parser))
	{
		redirect = parse_redirect(parser);
		if (redirect == NULL)
		{
			ft_list_destroy(redirects, destroy_redirect_helper);
			return (NULL);
		}
		ft_list_push_back(redirects, redirect);
	}
	if (peek_token(parser, TK_WORD))
		node = parse_word_cmd_suffix(parser);
	else
		node = new_ast_node(N_COMMAND, NULL, NULL);
	set_redirects(node, redirects);
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
