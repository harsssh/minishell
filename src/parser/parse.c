/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:01:43 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/19 16:45:24 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "ast.h"
#include "token.h"
#include "lexer.h"

t_ast_node	*parse(char *input)
{
	t_token_stream	*stream;
	t_parser		*parser;
	t_ast_node		*result;

	stream = tokenize(input);
	if (stream == NULL)
		return (NULL);
	parser = new_parser(stream);
	if (parser == NULL)
	{
		destroy_token_stream(stream);
		return (NULL);
	}
	return (parse_and_or(parser));
}
