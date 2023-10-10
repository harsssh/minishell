/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 23:53:22 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/09 21:48:07 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_INTERNAL_H
# define WORD_EXPANSION_INTERNAL_H

# include "context.h"

# define IFS_WHITESPACE " \t\n"

typedef struct s_word {
	char	*content;
	bool	is_expanded;
	char	quote;
	bool	is_end_here;
	bool	is_delimiter;
}	t_word;

t_list	*expand_parameter(char *word, t_context *ctx);
t_word	*new_word(char *content, bool is_expanded, char quote);
void	destroy_word(void *word);
void	*copy_word(void *word);
t_list	*split_word(t_list *expanded_words, t_context *ctx);
int		push_delimiter(t_list *res);
t_list	*remove_quotes_iter(t_list *splited_words);

#endif
