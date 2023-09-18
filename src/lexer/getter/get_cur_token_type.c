/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cur_token_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:41:35 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:41:45 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer_internal.h"

t_token_type	get_cur_token_type(t_lexer *lexer)
{
	return (lexer->cur_type);
}
