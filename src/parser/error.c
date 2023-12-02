/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:07:32 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/02 21:15:51 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser_internal.h"
#include "context.h"
#include <unistd.h> 

void	print_syntax_error(t_context *ctx, t_parser *parser)
{
	ft_dprintf(STDERR_FILENO, "%s: syntax error near unexpected token `%s'\n",
		ctx->shell_name, get_token_literal(get_cur_token(parser)));
}
