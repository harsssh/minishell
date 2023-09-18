/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_snapshot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:41:57 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 15:42:19 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer_internal.h"

char	*get_input_snapshot(t_lexer *lexer)
{
	return (lexer->input_snapshot);
}
