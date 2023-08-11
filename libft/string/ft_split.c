/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:13:26 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/20 15:06:05 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdlib.h"
#include <stdlib.h>

static char	*skip_char(const char *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

static char	*find(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	return ((char *)s);
}

static size_t	count_words(const char *s, char c)
{
	size_t	n;
	char	*t;

	n = 0;
	while (*s)
	{
		s = skip_char(s, c);
		t = find(s, c);
		if (s != t)
			n++;
		s = t;
	}
	return (n);
}

static char	**store_word(char **buf, size_t index, const char *begin,
		const char *end)
{
	size_t	i;

	if (begin == end)
		return (NULL);
	buf[index] = ft_substr(begin, 0, end - begin);
	if (buf[index] == NULL)
	{
		i = 0;
		while (buf[i])
			free(buf[i++]);
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	size_t	i;
	char	**buf;
	char	*end;

	if (s == NULL)
		return (NULL);
	wc = count_words(s, c);
	buf = ft_calloc(wc + 1, sizeof(char *));
	if (buf == NULL)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		s = skip_char(s, c);
		end = find(s, c);
		if (store_word(buf, i++, s, end) == NULL)
			return (NULL);
		s = end;
	}
	buf[i] = NULL;
	return (buf);
}
