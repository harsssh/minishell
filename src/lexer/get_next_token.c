/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:54:23 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/18 19:29:54 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "token.h"

t_token	*tokenize_operators(t_lexer *lexer)
{
	if (consume_input(lexer, "&&"))
		return (new_token(TK_AND, get_input_snapshot(lexer), 2));
	else if (consume_input(lexer, "||"))
		return (new_token(TK_OR, get_input_snapshot(lexer), 2));
	else if (consume_input(lexer, "|"))
		return (new_token(TK_PIPE, get_input_snapshot(lexer), 1));
	else if (consume_input(lexer, "<<"))
	{
		if (ft_isspace(get_cur_char(lexer)))
			return (new_token(TK_REDIRECT_APPEND,
					get_input_snapshot(lexer), 2));
		return (new_token(TK_REDIRECT_HERE_DOC, get_input_snapshot(lexer), 2));
	}
	else if (consume_input(lexer, "<"))
		return (new_token(TK_REDIRECT_IN, get_input_snapshot(lexer), 1));
	else if (consume_input(lexer, ">"))
		return (new_token(TK_REDIRECT_OUT, get_input_snapshot(lexer), 1));
	else
	{
		set_cur_token_type(lexer, TK_WORD);
		read_char(lexer);
		return (NULL);
	}
}

void	get_next_token_helper(t_lexer *lexer)
{
	take_input_snapshot(lexer);
	reset_token_len(lexer);
	skip_whitespaces(lexer);
	set_cur_token_type(lexer, TK_UNKNOWN);
}

void	tokenize_quotes(t_lexer *lexer)
{
	if (!is_quoted(lexer))
	{
		set_quote_char(lexer, get_cur_char(lexer));
		set_cur_token_type(lexer, TK_WORD);
	}
	else if (get_quote_char(lexer) == get_cur_char(lexer))
		end_quote(lexer);
	read_char(lexer);
}

t_token	*get_next_token(t_lexer *lexer)
{
	char	cur_char;
	t_token	*token;	

	get_next_token_helper(lexer);
	while (!has_empty_input(lexer))
	{
		cur_char = get_cur_char(lexer);
		if (cur_char == '\'' || cur_char == '"')
			tokenize_quotes(lexer);
		else if (is_quoted(lexer))
			read_char(lexer);
		else if (ft_isspace(cur_char))
		{
			skip_char(lexer);
			break ;
		}
		else
		{
			token = tokenize_operators(lexer);
			if (get_cur_token_type(lexer) != TK_WORD)
				return (token);
		}
	}
	return (new_token(get_cur_token_type(lexer),
			get_input_snapshot(lexer), get_token_len(lexer)));
}