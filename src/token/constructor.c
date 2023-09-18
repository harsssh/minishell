/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:38:40 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:43:14 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "token.h"
#include <stdlib.h>

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
	ft_memcpy(token->literal, input, token_len);
	token->type = type;
	return (token);
}

t_token_stream	*new_token_stream(void)
{
	return (ft_list_create());
}
