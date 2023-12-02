/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:08:16 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/30 01:40:37 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "token.h"
# include <stdbool.h>

typedef struct s_lexer
{
	char			*input;
	char			*input_snapshot;
	size_t			cur_token_len;
	char			quote_char;
	bool			do_escape_next_char;
	t_token_type	cur_type;
}	t_lexer;

t_lexer			*new_lexer(char *input);
void			destroy_lexer(t_lexer *lexer);
char			*get_input(t_lexer *lexer);
char			get_cur_char(t_lexer *lexer);
char			get_quote_char(t_lexer *lexer);
size_t			get_cur_token_len(t_lexer *lexer);
int				has_empty_input(t_lexer *lexer);
void			skip_whitespaces(t_lexer *lexer);
void			read_char(t_lexer *lexer);
void			reset_token_len(t_lexer *lexer);
int				is_quoted(t_lexer *lexer);
void			set_quote_char(t_lexer *lexer, char quote_char);
void			end_quote(t_lexer *lexer);
int				consume_input(t_lexer *lexer, char *expected);
void			set_cur_token_type(t_lexer *lexer, t_token_type type);
t_token_type	get_cur_token_type(t_lexer *lexer);
void			take_input_snapshot(t_lexer *lexer);
char			*get_input_snapshot(t_lexer *lexer);
t_token			*get_next_token(t_lexer *lexer);
void			skip_char(t_lexer *lexer);
int				peek_input(t_lexer *lexer, char *expected);

#endif
