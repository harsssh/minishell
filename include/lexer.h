/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:34:26 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/02 21:40:06 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "context.h"

typedef enum e_tokenize_result
{
	TRESULT_OK,
	TRESULT_UNMATCHING_QUOTE,
	TRESULT_MALLOC_ERROR,
}	t_tokenize_result;

t_tokenize_result	tokenize(char *input,
						t_token_stream **stream, t_context *ctx);

#endif
