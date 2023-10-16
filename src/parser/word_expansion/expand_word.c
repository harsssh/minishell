/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:05:26 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/10 17:24:11 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "ft_list.h"
#include "libft.h"
#include "variables.h"
#include <stdlib.h>
#include "word_expansion_internal.h"

static void	*word_to_str(void *word)
{
	if (word == NULL)
		return (NULL);
	return (ft_strdup(((t_word *)word)->content));
}

static t_list	*new_list_from_str(char *str)
{
	t_word	*word;
	t_list	*list;

	word = new_word(str, false, '\0');
	if (word == NULL)
		return (NULL);
	list = ft_list_create();
	if (list == NULL)
	{
		destroy_word(word);
		return (NULL);
	}
	if (ft_list_push_back(list, word) == NULL)
	{
		destroy_word(word);
		return (NULL);
	}
	return (list);
}

static t_list	*expand_word_helper(char *word, t_context *ctx, bool has_dollar)
{
	t_list	*expanded_words;
	t_list	*splited_words;
	t_list	*quote_removed;
	t_list	*res;

	if (has_dollar)
	{
		expanded_words = expand_parameter(word, ctx);
		if (expanded_words == NULL)
			return (NULL);
		splited_words = split_word(expanded_words, ctx);
		ft_list_destroy(expanded_words, destroy_word);
	}
	else
		splited_words = new_list_from_str(word);
	if (splited_words == NULL)
		return (NULL);
	quote_removed = remove_quotes_iter(splited_words);
	ft_list_destroy(splited_words, destroy_word);
	if (quote_removed == NULL)
		return (NULL);
	res = ft_list_copy(quote_removed, word_to_str, free);
	ft_list_destroy(quote_removed, destroy_word);
	return (res);
}

t_list	*expand_word(char *word, t_context *ctx, bool has_dollar)
{
	t_list	*new_words;

	if (word == NULL || ctx == NULL)
		return (NULL);
	if (has_dollar)
		return (expand_word_helper(word, ctx, has_dollar));
	else
	{
		new_words = ft_list_create();
		if (new_words == NULL
			|| ft_list_push_back(new_words, word) == NULL)
		{
			ft_list_destroy(new_words, free);
			return (NULL);
		}
		return (new_words);
	}
}
