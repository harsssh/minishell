/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_cmd_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:31 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/12 19:21:33 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_list.h"
#include "parser_internal.h"
#include "token.h"
#include <stdlib.h>

char	*parse_word(t_parser *parser)
{
	t_token	*token;
	char	*word;

	if (!peek_token(parser, TK_WORD))
		return (NULL);
	token = get_cur_token(parser);
	word = get_token_literal(token);
	if (token == NULL || word == NULL)
		return (NULL);
	word = ft_strdup(word);
	if (word == NULL)
		return (NULL);
	eat_token(parser);
	return (word);
}

static int	parse_cmd_suffix_helper_redirect(t_parser *parser, t_ast_node *node)
{
	t_redirect	*redirect;

	redirect = parse_redirect(parser);
	if (redirect == NULL
		|| add_node_redirect(node, redirect))
	{
		destroy_redirect(redirect);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	parse_cmd_suffix_helper(t_parser *parser,
								t_ast_node *node, bool *flag)
{
	char	*word;

	if (peek_redirect(parser))
	{
		*flag = true;
		if (parse_cmd_suffix_helper_redirect(parser, node))
			return (EXIT_FAILURE);
	}
	else if (peek_token(parser, TK_WORD))
	{
		*flag = true;
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

// ( io_redirect | 'WORD' )+
int	parse_cmd_suffix(t_parser *parser, t_ast_node *node)
{
	bool	is_parsed;

	is_parsed = false;
	if (parse_cmd_suffix_helper(parser, node, &is_parsed)
		|| !is_parsed)
		return (EXIT_FAILURE);
	while (!is_eof(parser))
	{
		is_parsed = false;
		if (parse_cmd_suffix_helper(parser, node, &is_parsed))
			return (EXIT_FAILURE);
		if (!is_parsed)
			break ;
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
	if (command_name == NULL || add_node_argv(node, command_name))
	{
		destroy_node(node);
		free(command_name);
		return (NULL);
	}
	if ((peek_token(parser, TK_WORD) || peek_redirect(parser))
		&& parse_cmd_suffix(parser, node))
	{
		free(command_name);
		return (NULL);
	}
	return (node);
}
