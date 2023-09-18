/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:39:01 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/14 04:47:24 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	get_token_type(t_token *token)
{
	if (token == NULL)
		return (TK_UNKNOWN);
	return (token->type);
}
