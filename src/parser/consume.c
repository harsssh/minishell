/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:38:25 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/22 17:56:26 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "parser_internal.h"
#include "token.h"

void	eat_token(t_parser *parser)
{
	t_token	*next_token;

	destroy_token(get_cur_token(parser));
	next_token = ft_list_pop_front(get_stream(parser));
	set_cur_token(parser, next_token);
}

bool	consume_token(t_parser *parser, t_token_type type)
{
	if (peek_token(parser, type))
	{
		eat_token(parser);
		return (1);
	}
	return (0);
}

bool	peek_token(t_parser *parser, t_token_type type)
{
	return (get_token_type(get_cur_token(parser)) == type);
}

bool	peek_redirect(t_parser *parser)
{
	return (peek_token(parser, TK_REDIRECT_IN)
		|| peek_token(parser, TK_REDIRECT_OUT)
		|| peek_token(parser, TK_REDIRECT_APPEND)
		|| peek_token(parser, TK_REDIRECT_HERE_DOC));
}
