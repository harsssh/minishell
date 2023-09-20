/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:34:14 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/20 19:30:48 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <sys/stat.h>
#include <stdlib.h>

bool	is_existing_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

bool	is_absolute_path(const char *path)
{
	return (path != NULL && *path == '/');
}

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
