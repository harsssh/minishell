/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:03:47 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/18 18:12:19 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "context.h"
#include "word_expansion_internal.h"

static void	*destroy_and_return_null(t_list *list, char *s)
{
	ft_list_destroy(list, free);
	free(s);
	return (NULL);
}

static void	update_quote(char *quote, char c)
{
	if (*quote == '\0')
		*quote = c;
	else if (*quote == c)
		*quote = '\0';
}

static char	*expand_paramters_helper(char *res, const char **word,
								t_context *ctx)
{
	char	*param;
	char	*joined;

	param = expand_first_param(word, ctx);
	if (param == NULL)
	{
		free(res);
		return (NULL);
	}
	joined = ft_strjoin(res, param);
	free(res);
	free(param);
	if (joined == NULL)
	{
		free(joined);
		return (NULL);
	}
	return (joined);
}

// char * -> t_list<char *>
// Returns a list with a single word, 
// assuming that param `word` is not NULL.
t_list	*expand_parameters(const char *word, t_context *ctx)
{
	char	*res;
	char	quote;
	t_list	*list;

	res = ft_strdup("");
	quote = '\0';
	while (*word != '\0')
	{
		if (*word == '$' && quote != '\'')
		{
			res = expand_paramters_helper(res, &word, ctx);
			if (res == NULL)
				return (NULL);
			continue ;
		}
		else if (*word == '\'' || *word == '"')
			update_quote(&quote, *word);
		res = join_char(res, &word);
		if (res == NULL)
			return (NULL);
	}
	list = ft_list_create();
	if (list == NULL || ft_list_push_back(list, res) == NULL)
		return (destroy_and_return_null(list, res));
	return (list);
}
