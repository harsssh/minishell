/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:17:17 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/09 21:47:53 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "word_expansion_internal.h"
#include <stdlib.h>

static char	*strjoin_char(char *s1, char c)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1);
	res = ft_calloc(len + 2, sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, len);
	res[len] = c;
	return (res);
}

static int	helper_internal(char *p, char *quote, t_list *res, t_word *word)
{
	char	*tmp;

	if (*p == *quote)
		*quote = '\0';
	else if ((*p == '\'' || *p == '\"') && *quote == '\0')
		*quote = *p;
	else
	{
		tmp = strjoin_char(res->tail->data, *p);
		if (tmp == NULL)
		{
			destroy_word(word);
			ft_list_destroy(res, destroy_word);
			return (EXIT_FAILURE);
		}
		free(word->content);
		word->content = tmp;
	}
	return (EXIT_SUCCESS);
}

static int	remove_quotes_iter_helper(t_list *splited_words, t_list *res,
									char *quote)
{
	t_word	*word;
	char	*p;

	word = ft_list_pop_front(splited_words);
	if (word->is_delimiter || res->head == NULL)
	{
		if (!ft_list_push_back(res, word))
			return (EXIT_SUCCESS);
		destroy_word(word);
		ft_list_destroy(res, destroy_word);
		return (EXIT_FAILURE);
	}
	p = word->content;
	while (*p != '\0')
	{
		if (helper_internal(p, quote, res, word))
			return (EXIT_FAILURE);
		p++;
	}
	destroy_word(word);
	return (EXIT_SUCCESS);
}

t_list	*remove_quotes_iter(t_list *splited_words)
{
	t_list	*res;
	char	quote;

	if (splited_words == NULL)
		return (NULL);
	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	quote = '\0';
	while (splited_words->head != NULL)
	{
		if (remove_quotes_iter_helper(splited_words, res, &quote))
		{
			ft_list_destroy(splited_words, destroy_word);
			return (NULL);
		}
	}
	return (res);
}
