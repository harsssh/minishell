/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:20:38 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 18:49:58 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int	is_quoted(t_lexer *lexer)
{
	return (lexer->quote_char != '\0');
}

void	set_quote_char(t_lexer *lexer, char quote_char)
{
	lexer->quote_char = quote_char;
}

void	end_quote(t_lexer *lexer)
{
	lexer->quote_char = '\0';
}
