/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:01:43 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 20:18:56 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "ast.h"
#include "token.h"

t_ast_node	*parse(t_token_stream *stream)
{
	t_parser	*parser;

	parser = new_parser(stream);
	if (parser == NULL)
		return (NULL);
	return (parse_and_or(parser));
}
