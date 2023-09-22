/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:05:07 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/20 21:57:21 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "token.h"
# include "ast.h"

typedef struct s_parser {
	t_token_stream	*stream;
	t_token			*cur_token;
}	t_parser;

bool			is_eof(t_parser *parser);
t_token			*get_cur_token(t_parser *parser);
t_token_stream	*get_stream(t_parser *parser);
void			set_cur_token(t_parser *parser, t_token *token);
bool			consume_token(t_parser *parser, t_token_type type);
void			eat_token(t_parser *parser);
bool			peek_token(t_parser *parser, t_token_type type);
bool			peek_redirect(t_parser *parser);
t_ast_node		*parse_word_cmd_suffix(t_parser *parser);
char			*parse_word(t_parser *parser);

#endif
