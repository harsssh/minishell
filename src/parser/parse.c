/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:01:43 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 21:53:33 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser_internal.h"
#include "ast.h"
#include "token.h"
#include "lexer.h"

t_ast_node	*parse(const char *input, t_context *ctx)
{
	t_parser	*parser;
	char		*trimmed_input;
	t_ast_node	*result;

	trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
	if (input == NULL)
		return (NULL);
	parser = new_parser(trimmed_input, ctx);
	free(trimmed_input);
	if (parser == NULL)
		return (NULL);
	result = parse_and_or(parser);
	if (!is_eof(parser))
	{
		destroy_parser(parser);
		destroy_node(result);
		return (NULL);
	}
	destroy_parser(parser);
	return (result);
}