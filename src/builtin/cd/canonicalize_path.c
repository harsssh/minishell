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

// 解決するときに, 各ディレクトリは存在するのかを確認する
// ./INVALID/../VALID -> ./VALID にはならない (単純な文字列操作ではだめ)
char	*canonicalize_path(char *path, bool check_existence)
{
	char *buf;
	char *ret;

	if (path == NULL)
		return (NULL);
	buf = ft_strdup(path);
	if (buf == NULL)
		return (NULL);
	ret = buf;
	// bufには構築中のパス (末尾はslashなし): /path/to/dir
	// pathは読んでいるパス (先頭はスラッシュでない): path/[to/dir]
	while (*path)
	{
		if (*path == '/')
			++path;
		else if (*path == '.' && (path[1] == '/' || path[1] == '\0'))
			++path;
		else if (ft_strncmp(path, "..", 2) == 0 && (path[1] == '/' || path[1] == '\0'))
		{
			// /INVALID/../ は, これまで構築したパスが有効化どうかを確認
			// TODO: bufに何も入っていなかったら? 空文字でチェックが入る
			*buf = '\0';
			if (check_existence && !is_existing_directory(ret)) {
				free(ret);
				return (NULL);
			}
			// /path/to -> /path (/ の前まで戻す)
			// /path -> /, / -> / (/ の前がなければ, / のまま)
			// .. -> ../.., . -> .., path -> . (/ がない. どうしよう)
		} else {
			// /path/[to]/dir, /path/to/[dir]
			if (buf != ret)
				*buf++ = '/';
			while(*path && *path != '/')
				*buf++ = *path++;
			*buf = '\0';
			if (check_existence && !is_existing_directory(ret)) {
				free(ret);
				return (NULL);
			}
		}
	}
	return (ret);
}
