/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:39:26 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/19 16:49:34 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
