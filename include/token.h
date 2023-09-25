/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:37:25 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/25 18:58:22 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

typedef enum e_token_type
{
	TK_UNKNOWN,
	TK_EOF,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_REDIRECT_APPEND,
	TK_REDIRECT_HERE_DOC,
	TK_WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*literal;
}	t_token;

t_token_type	get_token_type(t_token *token);
t_token			*new_token(t_token_type type, char *input, size_t token_len);
void			destroy_token(t_token *token);
char			*get_token_literal(t_token *token);
t_token			*clone_token(t_token *token);

typedef t_list	t_token_stream;

int				push_token(t_token_stream *stream, t_token *token);
t_token_stream	*new_token_stream(void);
void			destroy_token_stream(t_token_stream *stream);

#endif
