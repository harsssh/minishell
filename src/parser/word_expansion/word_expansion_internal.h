/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:58:11 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/29 10:32:20 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_INTERNAL_H
# define WORD_EXPANSION_INTERNAL_H

# include "context.h"
# include "libft.h"

typedef struct s_match_table
{
	bool	**dp;
	size_t	text_len;
	size_t	pat_len;
}	t_match_table;

t_list	*expand_word(const char *word, t_context *ctx);
t_list	*expand_parameters(const char *word, t_context *ctx);
char	*expand_first_param(const char **word, t_context *ctx);
t_list	*split_word(t_list *list);
char	*join_char(char *str, const char **word);
t_list	*remove_quotes(t_list *input);
t_list	*expand_filenames(t_list *input, char *cwd);
bool	reg_is_match(char *text, char *pat, bool *is_failed);

#endif
