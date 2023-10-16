/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:29:31 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/09 21:31:30 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "libft.h"
#include "context.h"
#include "variables.h"
#include "word_expansion_internal.h"

static int	append_word(t_list *res, t_word *word)
{
	t_word	*cpy_word;

	if (res->tail != NULL && ((t_word *)res->tail->data)->is_end_here)
	{
		if (push_delimiter(res))
			return (EXIT_FAILURE);
	}
	cpy_word = copy_word(word);
	if (cpy_word == NULL)
		return (EXIT_FAILURE);
	if (ft_list_push_back(res, cpy_word) != NULL)
	{
		destroy_word(cpy_word);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	end_with_last_word(t_list *res)
{
	t_word	*last_word;

	if (res->tail == NULL)
		return ;
	last_word = res->tail->data;
	last_word->is_end_here = true;
}

static int	split_expanded_word(t_word *word, t_list *res, const char *set)
{
	char	*p;
	char	*word_begin;
	char	*new_content;

	p = word->content;
	while (*p != '\0')
	{
		while (ft_strchr(set, *p) != NULL)
		{
			end_with_last_word(res);
			p++;
		}
		word_begin = p;
		while (ft_strchr(set, *p) == NULL)
			p++;
		new_content = ft_substr(word_begin, 0, p - word_begin);
		word = new_word(new_content, true, '\0');
		free(new_content);
		if (new_content == NULL || word == NULL || append_word(res, word))
		{
			destroy_word(word);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static t_list	*split_word_iter(t_list *expanded_words, const char *set)
{
	t_list	*res;
	t_node	*node;
	t_word	*word;
	int		status;

	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	node = expanded_words->head;
	while (node != NULL)
	{
		word = node->data;
		if (!word->is_expanded || word->quote != '\0')
			status = append_word(res, word);
		else
			status = split_expanded_word(word, res, set);
		if (status)
		{
			ft_list_destroy(res, destroy_word);
			return (NULL);
		}
		node = node->next;
	}
	return (res);
}

// (t_list<t_word *>, t_context *) -> t_list<t_word *>
t_list	*split_word(t_list *expanded_words, t_context *ctx)
{
	t_variable	*ifs;
	const char	*set;

	if (expanded_words == NULL)
		return (NULL);
	ifs = getvar(ctx, "IFS");
	if (ifs == NULL)
		set = " \t\n";
	else
		set = ifs->value;
	if (*set == '\0')
		return (ft_list_copy(expanded_words, copy_word, destroy_word));
	return (split_word_iter(expanded_words, set));
}
