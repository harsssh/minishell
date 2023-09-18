/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:41:16 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:41:23 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer_internal.h"

size_t	get_token_len(t_lexer *lexer)
{
	return (lexer->cur_token_len);
}
