/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:58:11 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/03 19:16:05 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_INTERNAL_H
# define WORD_EXPANSION_INTERNAL_H

# include "context.h"
# include "ft_list.h"
# include "libft.h"
# include <dirent.h>

# define NOT_EXPAND_IN_SINGLE_QUOTE 0
# define EXPAND_ANYWAY 1

typedef struct s_match_table
{
	bool	**dp;
	size_t	text_len;
	size_t	pat_len;
	size_t	i;
	size_t	j;
}	t_match_table;

t_list				*expand_parameters(const char *word, t_context *ctx,
						bool do_force_expand);
char				*expand_first_param(const char **word, t_context *ctx);
t_list				*split_word(t_list *list);
char				*join_char(char *str, const char **word);
char				*join_char_or_back_slash_char(char *str, const char **word);
t_list				*remove_quotes(t_list *input);
t_list				*expand_filenames(t_list *input);
bool				reg_is_match(char *text, char *pat, bool *is_failed);
t_list				*expand_filename(char *pat, t_list *cur_dir_filenames);
t_list				*get_cur_dir_filenames(void);
char				*escape_string(const char *str);

#endif
