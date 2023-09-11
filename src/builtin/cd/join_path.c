/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:21:58 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/20 17:21:59 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*join_path(char *base, char *relpath)
{
	char	*joined_path;
	char	*p;

	if (base == NULL || relpath == NULL)
		return (NULL);
	joined_path = malloc(ft_strlen(base) + ft_strlen(relpath) + 2);
	if (joined_path == NULL)
		return (NULL);
	p = joined_path;
	while (*base)
		*p++ = *base++;
	if (p > joined_path && *relpath && p[-1] != '/')
		*p++ = '/';
	while (*relpath)
		*p++ = *relpath++;
	*p = '\0';
	return (joined_path);
}
