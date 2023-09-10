/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:22:06 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/20 17:22:07 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_internal.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/stat.h>

// static bool is_existing_directory(char *path)
// {
// 	struct stat st;

// 	if (stat(path, &st) != 0)
// 		return (false);
// 	return (S_ISDIR(st.st_mode));
// }

/*
/path/to/.. -> /path	| /path/to 	: 前の / まで戻す
/path/.. 	-> /		| /path 	: 最初の / の次まで戻す
/.. 		-> /		| /			: 最初の / の次まで戻す
path/.. 	-> .		| path 		: 最初に戻す
.. 			-> .		| ""		: 最初に戻す
*/
// /path/INVALID/.. は /path じゃない
char	*canonicalize_path(char *path, bool check_existence)
{
	char	*buf;
	char	*ret;
	char 	*prev_slash;
	bool	is_absolute_path;

	(void)check_existence;
	if (path == NULL)
		return (NULL);
	buf = ft_strdup(path);
	if (buf == NULL)
		return (NULL);
	ret = buf;
	is_absolute_path = false;
	if (*path == '/')
	{
		*buf++ = *path++;
		is_absolute_path = true;
	}
	while (*path)
	{
		if (*path == '/')
			++path;
		else if (*path == '.' && (path[1] == '/' || path[1] == '\0'))
			++path;
		else if (ft_strncmp(path, "..", 2) == 0 && (path[2] == '/' || path[2] == '\0'))
		{
			// strrchrで戻る。先頭だったらその次、/がなければ最初に
			*buf = '\0';
			prev_slash = ft_strrchr(buf, '/');
			if (prev_slash == NULL)
				buf = ret;
			else if (prev_slash == ret)
				buf = ret + 1;
			else
				buf = prev_slash;
			path += 2;
		} else {
			if (buf != ret && buf[-1] != '/')
				*buf++ = '/';
			while(*path && *path != '/')
				*buf++ = *path++;
		}
	}
	if (buf == ret)
	{
		if (is_absolute_path)
			*buf++ = '/';
		else
			*buf++ = '.';
	}
	*buf = '\0';
	return (ret);
}
