/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:27:31 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/25 19:02:06 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "parser_internal.h"	

bool	is_eof(t_parser *parser)
{
	return (get_token_type(get_cur_token(parser)) == TK_EOF);
}
