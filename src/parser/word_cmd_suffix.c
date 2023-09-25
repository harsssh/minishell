/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_cmd_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:31 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/25 14:56:12 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include <stdlib.h>

char	*parse_word(t_parser *parser)
{
	char	*word;

	if (!peek_token(parser, TK_WORD))
		return (NULL);
	word = get_token_literal(get_cur_token(parser));
	if (word == NULL)
		return (NULL);
	word = ft_strdup(word);
	eat_token(parser);
	return (word);
}

// ( io_redirect | 'WORD' )+
int	parse_cmd_suffix(t_parser *parser, t_ast_node *node)
{
	t_redirect	*redirect;
	char		*word;

	while (!is_eof(parser))
	{
		if (peek_redirect(parser))
		{
			redirect = parse_redirect(parser);
			if (redirect == NULL
				|| add_node_redirect(node, redirect))
			{
				destroy_redirect(redirect);
				return (EXIT_FAILURE);
			}
			continue ;
		}
		word = parse_word(parser);
		if (word == NULL
			|| add_node_argv(node, word))
		{
			free(word);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

// 'WORD' cmd_suffix?
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
		|| ((peek_token(parser, TK_WORD) || peek_redirect(parser))
			&& parse_cmd_suffix(parser, node)))
	{
		destroy_node(node);
		free(command_name);
		return (NULL);
	}
	return (node);
}
