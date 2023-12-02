/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:48:14 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/02 21:45:21 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "libft.h"
#include "word_expansion_internal.h"
#include <stdlib.h>

char	*join_char_or_back_slash_char(char *str, const char **word)
{
	char	s[3];
	char	*res;
	size_t	join_len;

	ft_bzero(s, 3);
	if (**word == BACK_SLASH && (*word)[1] != '\0')
		join_len = 2;
	else
		join_len = 1;
	ft_memcpy(s, *word, join_len);
	*word += join_len;
	res = ft_strjoin(str, s);
	free(str);
	return (res);
}

char	*join_char(char *str, const char **word)
{
	char	s[2];
	char	*res;

	s[0] = **word;
	s[1] = '\0';
	res = ft_strjoin(str, s);
	free(str);
	(*word)++;
	return (res);
}

char	*escape_string(const char *str)
{
	char		*res;
	char		*tmp;

	res = ft_strdup("");
	if (res == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '"' || *str == BACK_SLASH)
		{
			tmp = res;
			res = ft_strjoin(tmp, "\\");
			free(tmp);
			if (res == NULL)
				return (NULL);
		}
		res = join_char(res, &str);
	}
	return (res);
}
