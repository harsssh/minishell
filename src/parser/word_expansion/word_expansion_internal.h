/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:58:11 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/20 13:51:50 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_INTERNAL_H
# define WORD_EXPANSION_INTERNAL_H

# include "context.h"
# include "libft.h"

t_list	*expand_word(const char *word, t_context *ctx);
t_list	*expand_parameters(const char *word, t_context *ctx);
char	*expand_first_param(const char **word, t_context *ctx);
t_list	*split_word(t_list *list);
char	*join_char(char *str, const char **word);
t_list	*remove_quotes(t_list *input);

#endif
