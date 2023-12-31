/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:54:38 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/03 18:10:28 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "token.h"
#include "lexer.h"
#include "utils.h"

t_parser	*new_parser(char *input, t_context *ctx)
{
	t_parser			*parser;
	t_token_stream		*stream;
	t_tokenize_result	tokenize_result;

	if (*input == '\0')
		return (NULL);
	tokenize_result = tokenize(input, &stream, ctx);
	if (tokenize_result != TRESULT_OK)
	{
		if (tokenize_result == TRESULT_UNMATCHING_QUOTE)
			print_simple_error(ctx, "parser", "unexpected token `newline'");
		ctx->last_exit_status = EXIT_SYNTAX_ERROR;
		return (NULL);
	}
	parser = ft_calloc(1, sizeof(t_parser));
	if (parser == NULL)
	{
		destroy_token_stream(stream);
		return (NULL);
	}
	parser->stream = stream;
	parser->ctx = ctx;
	eat_token(parser);
	return (parser);
}
