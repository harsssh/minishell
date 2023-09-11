/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:34:14 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 17:34:15 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/stat.h>

bool	is_existing_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}
