/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:35:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 01:35:22 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

static void	remove_trailing_slash(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	while (len > 1 && path[len - 1] == '/')
		path[--len] = '\0';
}

// This function returns the last component of the pathname path.
// The caller is responsible for freeing the returned string.
char	*ft_basename(const char *path)
{
	char	*copy_path;
	char	*last_slash;

	if (path == NULL)
		return (NULL);
	if (*path == '\0')
		return (ft_strdup("."));
	copy_path = ft_strdup(path);
	if (copy_path == NULL)
		return (NULL);
	remove_trailing_slash(copy_path);
	last_slash = ft_strrchr(copy_path, '/');
	if (last_slash == NULL || last_slash == copy_path)
		return (copy_path);
	ft_memmove(copy_path, last_slash + 1, ft_strlen(last_slash + 1) + 1);
	return (copy_path);
}
