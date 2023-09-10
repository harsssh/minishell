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

static bool is_existing_directory(char *path)
{
	struct stat st;

	if (stat(path, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

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
	char *buf;
	char *ret;
	char *tmp;

	if (path == NULL)
		return (NULL);
	buf = ft_strdup(path);
	if (buf == NULL)
		return (NULL);
	ret = buf;
	if (*path == '/')
		*buf++ = '/';
	tmp = buf;
	// bufには構築中のパス (末尾はslashなし): /path/to/dir
	// pathは読んでいるパス (先頭はスラッシュでない): path/[to/dir]
	while (*path)
	{
		if (*path == '/') // / は読み飛ばす
			++path;
		else if (*path == '.' && (path[1] == '/' || path[1] == '\0')) // ./ or . 
			++path;
		else if (ft_strncmp(path, "..", 2) == 0 && (path[1] == '/' || path[1] == '\0')) // ../ or ..
		{
		} else {
			// 最初でなければ, / を入れる
			if (buf != ret)
				*buf++ = '/';
			// / までコピー
			while(*path && *path != '/')
				*buf++ = *path++;
			*buf = '\0';
		}
	}
	return (ret);
}
