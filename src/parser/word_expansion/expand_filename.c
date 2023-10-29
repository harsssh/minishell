/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:49:57 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/30 03:31:12 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "libft.h"
#include <stdlib.h>
#include "word_expansion_internal.h"
#include <dirent.h>

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

	if (reg_is_match(pat, filename, &is_matching_failed))
	{
		filename = ft_strdup(filename);
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
static t_list	*get_cur_dir_filenames(char *cwd)
{
	DIR				*d;
	t_list			*res;
	struct dirent	*dir;
	char			*filename;

	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	d = opendir(cwd);
	if (d == NULL)
		return (destroy_and_return_null(NULL, res, NULL));
	dir = readdir(d);
	while (dir != NULL)
	{
		if (dir->d_type == DT_REG)
		{
			filename = ft_strdup(dir->d_name);
			if (filename == NULL || ft_list_push_back(res, filename) == NULL)
				return (destroy_and_return_null(filename, res, d));
		}
		dir = readdir(d);
	}
	closedir(d);
	return (res);
}

static t_list	*expand_filename(char *pat, t_list *cur_dir_filenames)
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

// t_list<char *> -> t_list<char *>
// TODO: match all possible patterns,
t_list	*expand_filenames(t_list *input, char *cwd)
{
	t_list	*res;
	char	*pat;
	t_list	*expanded;
	t_list	*cur_dir_filenames;

	res = ft_list_create();
	if (res == NULL)
		return (res);
	cur_dir_filenames = get_cur_dir_filenames(cwd);
	if (cur_dir_filenames == NULL)
		return (destroy_and_return_null(NULL, res, NULL));
	while (input->size != 0)
	{
		pat = ft_list_pop_front(input);
		expanded = expand_filename(pat, cur_dir_filenames);
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
