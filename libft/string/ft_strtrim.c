/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:43:59 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/21 18:16:57 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

// whether s contains c
static int	contains(const char *s, char c)
{
	return (ft_strchr(s, c) != NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	begin = 0;
	while (s1[begin] && contains(set, s1[begin]))
		begin++;
	end = ft_strlen(s1);
	while (begin < end && contains(set, s1[end - 1]))
		end--;
	if (begin >= end)
		return (ft_strdup(""));
	return (ft_substr(s1, begin, end - begin));
}
