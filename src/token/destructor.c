/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:54:50 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 13:52:02 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "token.h"
#include <stdlib.h>

void	destroy_token(t_token *token)
{
	if (token == NULL)
		return ;
	free(token->literal);
	free(token);
}

static void	destroy_token_stream_helper(void *data)
{
	destroy_token(data);
}

void	destroy_token_stream(t_token_stream *stream)
{
	ft_list_destroy(stream, destroy_token_stream_helper);
}
