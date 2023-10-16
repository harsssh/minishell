/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:14:53 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:37:37 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "lexer_internal.h"

t_lexer	*new_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->input = input;
	take_input_snapshot(lexer);
	return (lexer);
}

void	reset_token_len(t_lexer *lexer)
{
	lexer->cur_token_len = 0;
}
