/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:40:58 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:41:06 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer_internal.h"

char	get_quote_char(t_lexer *lexer)
{
	return (lexer->quote_char);
}
