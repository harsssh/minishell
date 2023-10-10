/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:38:40 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/05 20:47:35 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "token.h"
#include <stdlib.h>

static bool	new_token_memcpy(void *literal, const void *input, size_t token_len)
{
	unsigned char		*d;
	const unsigned char	*s;
	bool				has_dollar;

	has_dollar = false;
	if (literal == NULL && input == NULL)
		return (false);
	d = literal;
	s = input;
	while (token_len--)
	{
		if (*s == '$')
			has_dollar = true;
		*d++ = *s++;
	}
	return (has_dollar);
}

t_token	*new_token(t_token_type type, char *input, size_t token_len)
{
	t_token	*token;

	if (input == NULL)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->literal = ft_calloc(token_len + 1, sizeof(char));
	if (token->literal == NULL)
	{
		free(token);
		return (NULL);
	}
	token->has_dollar = new_token_memcpy(token->literal, input, token_len);
	token->type = type;
	return (token);
}

t_token_stream	*new_token_stream(void)
{
	return (ft_list_create());
}

t_token	*clone_token(t_token *token)
{
	return (new_token(get_token_type(token),
			get_token_literal(token), ft_strlen(get_token_literal(token))));
}
