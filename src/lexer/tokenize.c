/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:02:16 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/02 22:01:45 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "ft_ctype.h"
#include "lexer.h"
#include "lexer_internal.h"
#include <stdlib.h>
#include "token.h"

int	push_tokens(t_lexer *lexer, t_token_stream *stream)
{
	t_token			*cur_token;
	t_token_type	cur_type;

	if (stream == NULL || lexer == NULL)
		return (EXIT_FAILURE);
	cur_type = TK_UNKNOWN;
	while (cur_type != TK_EOF)
	{
		cur_token = get_next_token(lexer);
		cur_type = get_token_type(cur_token);
		if (cur_token == NULL
			|| cur_type == TK_UNKNOWN
			|| is_quoted(lexer)
			|| push_token(stream, cur_token))
		{
			destroy_token(cur_token);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

t_tokenize_result	tokenize(char *input,
							t_token_stream **stream, t_context *ctx)
{
	t_lexer			*lexer;
	int				is_tokenize_failed;

	if (input == NULL)
		return (TRESULT_MALLOC_ERROR);
	lexer = new_lexer(input);
	*stream = new_token_stream();
	is_tokenize_failed = push_tokens(lexer, *stream);
	if (lexer == NULL || *stream == NULL || is_tokenize_failed)
	{
		destroy_token_stream(*stream);
		*stream = NULL;
		if (get_quote_char(lexer) != '\0')
		{
			print_unmatching_quote_error(lexer, ctx);
			destroy_lexer(lexer);
			return (TRESULT_UNMATCHING_QUOTE);
		}
		destroy_lexer(lexer);
		return (TRESULT_MALLOC_ERROR);
	}
	destroy_lexer(lexer);
	return (TRESULT_OK);
}
