/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:54:38 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/22 18:26:15 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "token.h"
#include "lexer.h"

t_parser	*new_parser(char *input)
{
	t_parser		*parser;
	t_token_stream	*stream;

	stream = tokenize(input);
	if (stream == NULL)
		return (NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	if (parser == NULL)
	{
		destroy_token_stream(stream);
		return (NULL);
	}
	parser->stream = stream;
	eat_token(parser);
	return (parser);
}
