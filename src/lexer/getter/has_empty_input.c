/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_empty_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:46:33 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:46:38 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer_internal.h"

int	has_empty_input(t_lexer *lexer)
{
	return (lexer != NULL
		&& get_input(lexer) != NULL
		&& get_input(lexer)[0] == '\0');
}
