/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:48:14 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/20 21:36:49 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "libft.h"
#include "word_expansion_internal.h"
#include <stdlib.h>

char	*join_char(char *str, const char **word)
{
	char	s[3];
	char	*res;

	if (**word == BACK_SLASH)
	{
		s[0] = BACK_SLASH;
		if (s[1] != '\'' && s[1] != '"')
			return (NULL);
		s[1] = **word;
		s[2] = '\0';
	}
	else
	{
		s[0] = **word;
		s[1] = '\0';
	}
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
		if (*str == '\'' || *str == '"')
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
