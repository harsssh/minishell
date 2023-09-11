/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize_absolute_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:22:06 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 17:34:02 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_internal.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

typedef struct s_proc_state
{
	const char			*path;
	char				*result;
	char				*cur;
	bool				check_existence;
}						t_proc_state;

typedef t_proc_state	(*t_handler)(t_proc_state);

static t_proc_state	handle_skip(t_proc_state s)
{
	++s.path;
	return (s);
}

static t_proc_state	handle_double_dot(t_proc_state s)
{
	char	*prev_slash;

	*s.cur = '\0';
	if (s.check_existence && !is_existing_directory(s.result))
	{
		free(s.result);
		return (s);
	}
	prev_slash = ft_strrchr(s.result, '/');
	if (prev_slash == NULL)
		s.cur = s.result;
	else if (prev_slash == s.result)
		s.cur = s.result + 1;
	else
		s.cur = prev_slash;
	s.path += 2;
	return (s);
}

static t_proc_state	handle_path_segment(t_proc_state s)
{
	*s.cur = '\0';
	if (s.check_existence && !is_existing_directory(s.result))
	{
		free(s.result);
		s.cur = NULL;
		return (s);
	}
	if (s.cur != s.result && s.cur[-1] != '/')
		*s.cur++ = '/';
	while (*s.path && *s.path != '/')
		*s.cur++ = *s.path++;
	return (s);
}

static t_handler	get_handler(const char *path)
{
	if (*path == '/')
		return (handle_skip);
	if (*path == '.' && (path[1] == '/' || path[1] == '\0'))
		return (handle_skip);
	if (ft_strncmp(path, "..", 2) == 0 && (path[2] == '/' || path[2] == '\0'))
		return (handle_double_dot);
	return (handle_path_segment);
}

char	*canonicalize_absolute_path(const char *path, bool check_existence)
{
	t_proc_state	s;
	t_handler		handler;

	if (path == NULL || *path != '/')
		return (NULL);
	s.result = ft_strdup(path);
	if (s.result == NULL)
		return (NULL);
	s.check_existence = check_existence;
	s.path = path + 1;
	s.cur = s.result + 1;
	while (*s.path)
	{
		handler = get_handler(s.path);
		s = handler(s);
		if (s.cur == NULL)
			return (NULL);
	}
	*s.cur = '\0';
	return (s.result);
}
