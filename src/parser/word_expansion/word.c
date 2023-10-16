/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:14:08 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/10 17:24:34 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion_internal.h"
#include <stdlib.h>
#include "libft.h"

t_word	*new_word(char *content, bool is_expanded, char quote)
{
	t_word	*res;

	res = ft_calloc(1, sizeof(t_word));
	if (res == NULL || content == NULL)
		return (NULL);
	res->content = ft_strdup(content);
	if (res->content == NULL)
	{
		free(res);
		return (NULL);
	}
	res->is_expanded = is_expanded;
	res->quote = quote;
	return (res);
}

void	destroy_word(void *word)
{
	if (word == NULL)
		return ;
	free(((t_word *)word)->content);
	free(word);
}

void	*copy_word(void *word)
{
	t_word	*w;
	t_word	*res;

	if (word == NULL)
		return (NULL);
	w = word;
	res = new_word(w->content, w->is_expanded, w->quote);
	if (res == NULL)
		return (NULL);
	return (res);
}

int	push_delimiter(t_list *res)
{
	t_word	*word;

	word = new_word("", false, '\0');
	if (word == NULL)
		return (EXIT_FAILURE);
	word->is_delimiter = true;
	if (ft_list_push_back(res, word) == NULL)
	{
		destroy_word(word);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
