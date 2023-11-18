/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:16:28 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/19 03:01:20 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "word_expansion_internal.h"

#define BACK_SLASH '\\'

static void	read_quote(const char **s, char *quote)
{
	if (*quote == '\0')
		*quote = **s;
	else if (**s == *quote)
		*quote = '\0';
	(*s)++;
}

static char	*remove_quote(const char *s)
{
	char	quote;
	char	*res;

	quote = '\0';
	res = ft_strdup("");
	if (res == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if ((*s == '\'' || *s == '"') && (quote == '\0' || quote == *s))
			read_quote(&s, &quote);
		else
		{
			if (*s == BACK_SLASH)
				s++;
			res = join_char(res, &s);
			if (res == NULL)
				return (NULL);
		}
	}
	return (res);
}

t_list	*remove_quotes(t_list *input)
{
	t_list	*res;
	char	*tmp;
	char	*word;

	res = ft_list_create();
	if (res == NULL)
		return (res);
	while (input->size != 0)
	{
		tmp = ft_list_pop_front(input);
		word = remove_quote(tmp);
		free(tmp);
		if (word == NULL || ft_list_push_back(res, word) == NULL)
		{
			free(word);
			ft_list_destroy(res, free);
			return (NULL);
		}
	}
	return (res);
}
