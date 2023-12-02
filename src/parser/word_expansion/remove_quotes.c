/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:16:28 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/30 01:55:14 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "characters.h"
#include "libft.h"
#include "utils.h"
#include "word_expansion_internal.h"
#include <stdlib.h>

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
		if (is_quote(*s) && (quote == '\0' || quote == *s))
			read_quote(&s, &quote);
		else
		{
			if (quote == SINGLE_QUOTE || (*s == BACKSLASH && s[1] != '\0'
					&& ((quote == '\0' && ft_strchr("\\'\"$", s[1]))
						|| (quote == DOUBLE_QUOTE
							&& ft_strchr("\\\"$", s[1]))) && s++))
				res = join_char(res, &s);
			else
				res = join_char_or_back_slash_char(res, &s);
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
