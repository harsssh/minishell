/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:15:00 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/29 23:39:07 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "libft.h"
#include "characters.h"
#include "utils.h"
#include <stdlib.h>

static void	eat_escape_and_quote(char **input, char *quote)
{
	if (**input == BACKSLASH)
		(*input)++;
	else if (*quote == '\0')
		*quote = **input;
	else if (**input == *quote)
		*quote = '\0';
	if (**input != '\0')
		(*input)++;
}

static char	*get_next_word(char **input)
{
	char	quote;
	char	*p;
	char	*str;

	while (ft_strchr(" \t\n", **input) != NULL && **input != '\0')
		(*input)++;
	quote = '\0';
	p = *input;
	while (*p != '\0')
	{
		if (*p == BACKSLASH || is_quote(*p))
			eat_escape_and_quote(&p, &quote);
		else if (quote != '\0')
			p++;
		else if (ft_strchr(" \t\n", *p) != NULL)
			break ;
		else
			p++;
	}
	str = ft_substr(*input, 0, p - *input);
	if (str == NULL)
		return (NULL);
	*input = p;
	return (str);
}

static void	*destroy_and_return_null(t_list *l, char *w)
{
	ft_list_destroy(l, free);
	free(w);
	return (NULL);
}

t_list	*split_word(t_list *list)
{
	t_list	*res;
	char	*p;
	char	*word;

	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	p = list->head->data;
	while (1)
	{
		word = get_next_word(&p);
		if (word == NULL)
			return (destroy_and_return_null(res, word));
		if (*word == '\0')
		{
			free(word);
			return (res);
		}
		if (ft_list_push_back(res, word) == NULL)
			return (destroy_and_return_null(res, word));
	}
}
