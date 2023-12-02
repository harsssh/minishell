/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filenames.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:49:57 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/18 22:22:23 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "word_expansion_internal.h"
#include <stdlib.h>

static void	*destroy_and_return_null(char *s, t_list *l, DIR *d)
{
	free(s);
	ft_list_destroy(l, free);
	if (d != NULL)
		closedir(d);
	return (NULL);
}

static bool	is_pat(char *pat)
{
	while (*pat != '\0')
	{
		if (*pat == '*')
			return (true);
		pat++;
	}
	return (false);
}

static t_list	*expand_or_dup_filename(char *pat, t_list *cur_dir_filenames)
{
	t_list	*res;
	char	*filename;

	if (is_pat(pat))
		return (expand_filename(pat, cur_dir_filenames));
	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	filename = ft_strdup(pat);
	if (filename == NULL || ft_list_push_back(res, filename) == NULL)
	{
		free(filename);
		ft_list_destroy(res, free);
		return (NULL);
	}
	return (res);
}

// t_list<char *> -> t_list<char *>
// TODO: match all possible patterns,
t_list	*expand_filenames(t_list *input)
{
	t_list	*res;
	char	*pat;
	t_list	*expanded;
	t_list	*cur_dir_filenames;

	res = ft_list_create();
	if (res == NULL)
		return (res);
	cur_dir_filenames = get_cur_dir_filenames();
	if (cur_dir_filenames == NULL)
		return (destroy_and_return_null(NULL, res, NULL));
	while (input->size != 0)
	{
		pat = ft_list_pop_front(input);
		expanded = expand_or_dup_filename(pat, cur_dir_filenames);
		if (expanded == NULL)
		{
			ft_list_destroy(cur_dir_filenames, free);
			return (destroy_and_return_null(pat, res, NULL));
		}
		ft_list_append(res, expanded);
		free(pat);
	}
	ft_list_destroy(cur_dir_filenames, free);
	return (res);
}
