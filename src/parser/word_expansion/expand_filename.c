/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:45:58 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/18 21:25:13 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "word_expansion_internal.h"

static void	*destroy_and_return_null(char *s, t_list *l, DIR *d)
{
	free(s);
	ft_list_destroy(l, free);
	if (d != NULL)
		closedir(d);
	return (NULL);
}

static int	push_expanded_filename(char *filename, char *pat, t_list *res)
{
	bool	is_matching_failed;

	is_matching_failed = false;
	if (reg_is_match(filename, pat, &is_matching_failed))
	{
		filename = escape_string(filename);
		if (filename == NULL || ft_list_push_back(res, filename) == NULL)
		{
			destroy_and_return_null(filename, res, NULL);
			return (EXIT_FAILURE);
		}
	}
	else if (is_matching_failed)
	{
		destroy_and_return_null(NULL, res, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// TODO: handle errors from readdir and closedir
t_list	*get_cur_dir_filenames(void)
{
	DIR				*d;
	t_list			*res;
	struct dirent	*dir;
	char			*filename;

	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	d = opendir(".");
	if (d == NULL)
		return (destroy_and_return_null(NULL, res, NULL));
	dir = readdir(d);
	while (dir != NULL)
	{
		filename = ft_strdup(dir->d_name);
		if (filename == NULL || ft_list_push_back(res, filename) == NULL)
			return (destroy_and_return_null(filename, res, d));
		dir = readdir(d);
	}
	closedir(d);
	return (res);
}

t_list	*expand_filename(char *pat, t_list *cur_dir_filenames)
{
	t_list	*res;
	t_node	*filename_node;

	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	pat = ft_strdup(pat);
	if (pat == NULL)
		return (destroy_and_return_null(NULL, res, NULL));
	if (cur_dir_filenames->size == 0)
	{
		if (ft_list_push_back(res, pat) == NULL)
			return (destroy_and_return_null(pat, res, NULL));
		return (res);
	}
	filename_node = cur_dir_filenames->head;
	while (filename_node != NULL)
	{
		if (push_expanded_filename(filename_node->data, pat, res))
			return (destroy_and_return_null(pat, res, NULL));
		filename_node = filename_node->next;
	}
	if (res->size == 0 && ft_list_push_back(res, pat) == NULL)
		return (destroy_and_return_null(pat, res, NULL));
	return (res);
}
