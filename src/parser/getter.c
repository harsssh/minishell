/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:39:26 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/26 13:26:28 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "parser_internal.h"
#include "token.h"

t_token	*get_cur_token(t_parser *parser)
{
	return (parser->cur_token);
}

t_token_stream	*get_stream(t_parser *parser)
{
	return (parser->stream);
}

t_context	*get_parser_ctx(t_parser *parser)
{
	return (parser->ctx);
}
