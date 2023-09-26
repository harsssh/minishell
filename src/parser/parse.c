/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:01:43 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/26 13:24:31 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "ast.h"
#include "token.h"
#include "lexer.h"

t_ast_node	*parse(char *input, t_context *ctx)
{
	t_parser	*parser;

	parser = new_parser(input, ctx);
	if (parser == NULL)
		return (NULL);
	return (parse_and_or(parser));
}
