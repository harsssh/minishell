/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:21:23 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/02 21:33:58 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "ft_stdio.h"
#include "lexer/lexer_internal.h"
#include <unistd.h>

void	print_unmatching_quote_error(t_lexer *lexer, t_context *ctx)
{
	ft_dprintf(STDERR_FILENO,
		"%s: unexpected EOF while looking for matching `%c'\n",
		ctx->shell_name, get_quote_char(lexer));
}
