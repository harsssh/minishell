/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:39:01 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/05 20:47:54 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token_type	get_token_type(t_token *token)
{
	if (token == NULL)
		return (TK_UNKNOWN);
	return (token->type);
}

char	*get_token_literal(t_token *token)
{
	if (token == NULL)
		return (NULL);
	return (token->literal);
}

bool	has_dollar(t_token *token)
{
	return (token->type == TK_WORD && token->has_dollar);
}
