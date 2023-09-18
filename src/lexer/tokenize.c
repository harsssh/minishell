/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:02:16 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 19:44:28 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "lexer_internal.h"
#include <stdlib.h>
#include "token.h"

int	push_tokens(t_lexer *lexer, t_token_stream *stream)
{
	t_token			*cur_token;
	t_token_type	cur_type;

	if (stream == NULL || lexer == NULL)
		return (EXIT_FAILURE);
	while (!has_empty_input(lexer))
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

t_token_stream	*tokenize(char *input)
{
	t_lexer			*lexer;
	t_token_stream	*stream;
	int				is_tokenize_failed;

	if (input == NULL)
		return (NULL);
	lexer = new_lexer(input);
	stream = new_token_stream();
	is_tokenize_failed = push_tokens(lexer, stream);
	destroy_lexer(lexer);
	if (lexer == NULL || stream == NULL || is_tokenize_failed)
	{
		destroy_token_stream(stream);
		return (NULL);
	}
	return (stream);
}
