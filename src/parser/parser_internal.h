/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:05:07 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/02 22:19:47 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser.h"
# include "token.h"

typedef struct s_parser
{
	t_token_stream	*stream;
	t_token			*cur_token;
	t_context		*ctx;
}	t_parser;

t_parser		*new_parser(char *input, t_context *ctx);
bool			is_eof(t_parser *parser);
t_token			*get_cur_token(t_parser *parser);
t_token_stream	*get_stream(t_parser *parser);
t_context		*get_parser_ctx(t_parser *parser);
void			set_cur_token(t_parser *parser, t_token *token);
bool			consume_token(t_parser *parser, t_token_type type);
void			eat_token(t_parser *parser);
bool			peek_token(t_parser *parser, t_token_type type);
bool			peek_redirect(t_parser *parser);
t_ast_node		*parse_word_cmd_suffix(t_parser *parser);
char			*parse_word(t_parser *parser);
t_redirect		*parse_redirect(t_parser *parser);
t_list			*parse_redirects(t_parser *parser);
t_ast_node		*parse_simple_command(t_parser *parser);
t_ast_node		*parse_command(t_parser *parser);
t_ast_node		*parse_pipeline(t_parser *parser);
t_ast_node		*parse_and_or(t_parser *parser);
t_ast_node		*parse_complete_command(t_parser *parser);
t_redirect		*parse_here_doc(t_parser *parser);
t_list			*expand_word(char *word, t_context *ctx, bool has_dollar,
					bool is_expand);
void			destroy_word(void *word);
void			destroy_parser(t_parser *parser);
void			*destroy_nodes_and_return_null(t_ast_node *n1, t_ast_node *n2);

#endif
