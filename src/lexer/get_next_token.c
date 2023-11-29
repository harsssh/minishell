/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:54:23 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/29 23:42:35 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "token.h"
#include "characters.h"
#include "utils.h"

static t_token	*tokenize_operators(t_lexer *lexer)
{
	if (consume_input(lexer, "&&"))
		return (new_token(TK_AND, get_input_snapshot(lexer), 2));
	else if (consume_input(lexer, "||"))
		return (new_token(TK_OR, get_input_snapshot(lexer), 2));
	else if (consume_input(lexer, "|"))
		return (new_token(TK_PIPE, get_input_snapshot(lexer), 1));
	else if (consume_input(lexer, "<<"))
		return (new_token(TK_REDIRECT_HERE_DOC, get_input_snapshot(lexer), 2));
	else if (consume_input(lexer, "<"))
		return (new_token(TK_REDIRECT_IN, get_input_snapshot(lexer), 1));
	else if (consume_input(lexer, ">>"))
		return (new_token(TK_REDIRECT_APPEND, get_input_snapshot(lexer), 2));
	else if (consume_input(lexer, ">"))
		return (new_token(TK_REDIRECT_OUT, get_input_snapshot(lexer), 1));
	else if (consume_input(lexer, "("))
		return (new_token(TK_LPAREN, get_input_snapshot(lexer), 1));
	else if (consume_input(lexer, ")"))
		return (new_token(TK_RPAREN, get_input_snapshot(lexer), 1));
	else if (consume_input(lexer, ";"))
		return (new_token(TK_SEMICOLON, get_input_snapshot(lexer), 1));
	set_cur_token_type(lexer, TK_WORD);
	read_char(lexer);
	return (NULL);
}

static void	get_next_token_helper(t_lexer *lexer)
{
	skip_whitespaces(lexer);
	set_cur_token_type(lexer, TK_UNKNOWN);
	take_input_snapshot(lexer);
	reset_token_len(lexer);
}

static void	tokenize_quote_and_escape(t_lexer *lexer)
{
	if (get_cur_char(lexer) == BACKSLASH)
	{
		set_cur_token_type(lexer, TK_WORD);
		read_char(lexer);
		if (get_quote_char(lexer) != SINGLE_QUOTE && *get_input(lexer) != '\0')
			read_char(lexer);
		return ;
	}
	if (!is_quoted(lexer))
	{
		set_quote_char(lexer, get_cur_char(lexer));
		set_cur_token_type(lexer, TK_WORD);
	}
	else if (get_quote_char(lexer) == get_cur_char(lexer))
		end_quote(lexer);
	read_char(lexer);
}

static int	is_startwith_operator(t_lexer *lexer)
{
	return (peek_input(lexer, "&&") || peek_input(lexer, "|")
		|| peek_input(lexer, "<") || peek_input(lexer, ">")
		|| peek_input(lexer, "(") || peek_input(lexer, ")")
		|| peek_input(lexer, ";"));
}

t_token	*get_next_token(t_lexer *lexer)
{
	char	cur_char;
	t_token	*token;	

	get_next_token_helper(lexer);
	if (get_cur_char(lexer) == '\0')
		return (new_token(TK_EOF, get_input_snapshot(lexer), 0));
	while (!has_empty_input(lexer))
	{
		cur_char = get_cur_char(lexer);
		if (cur_char == BACKSLASH || is_quote(cur_char))
			tokenize_quote_and_escape(lexer);
		else if (is_quoted(lexer))
			read_char(lexer);
		else if (ft_isspace(cur_char) || (is_startwith_operator(lexer)
				&& get_cur_token_type(lexer) != TK_UNKNOWN))
			break ;
		else
		{
			token = tokenize_operators(lexer);
			if (get_cur_token_type(lexer) != TK_WORD)
				return (token);
		}
	}
	return (new_token(get_cur_token_type(lexer),
			get_input_snapshot(lexer), get_cur_token_len(lexer)));
}
