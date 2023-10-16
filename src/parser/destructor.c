/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:50:13 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 21:52:14 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser_internal.h"
#include "token.h"

void	destroy_parser(t_parser *parser)
{
	if (parser == NULL)
		return ;
	destroy_token_stream(parser->stream);
	destroy_token(parser->cur_token);
	free(parser);
}
