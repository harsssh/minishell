/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:08:50 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 19:23:23 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer_internal.h"

void	skip_char(t_lexer *lexer)
{
	if (get_cur_char(lexer) == '\0')
		return ;
	lexer->input++;
}

void	read_char(t_lexer *lexer)
{
	skip_char(lexer);
	lexer->cur_token_len++;
}

void	skip_whitespaces(t_lexer *lexer)
{
	while (ft_isspace(get_cur_char(lexer)))
		skip_char(lexer);
}

int	consume_input(t_lexer *lexer, char *expected)
{
	size_t	expected_len;

	if (ft_strncmp(expected, get_input_snapshot(lexer),
			ft_strlen(expected)) == 0)
	{
		expected_len = ft_strlen(expected);
		while (expected_len-- > 0)
			read_char(lexer);
		return (1);
	}
	return (0);
}
