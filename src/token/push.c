/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:42:16 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/14 04:45:11 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>

int	push_token(t_token_stream *stream, t_token *token)
{
	if (stream == NULL || token == NULL)
		return (EXIT_FAILURE);
	ft_list_push_back(stream, token);
	return (EXIT_SUCCESS);
}
