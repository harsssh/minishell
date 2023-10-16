/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:14:31 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:37:39 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	set_cur_token_type(t_lexer *lexer, t_token_type type)
{
	lexer->cur_type = type;
}

void	take_input_snapshot(t_lexer *lexer)
{
	lexer->input_snapshot = get_input(lexer);
}
