/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:40:17 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/09 21:24:01 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "ft_list.h"
#include "libft.h"
#include "variables.h"
#include <stdlib.h>
#include "word_expansion_internal.h"

static char	*take_first_param_value(t_context *ctx, char *s, char **endptr)
{
	char		*name;
	t_variable	*var;

	if (*s == '?')
	{
		*endptr = s + 1;
		return (ft_itoa(ctx->last_exit_status));
	}
	*endptr = s;
	if (!ft_isalpha(*s) && *s != '_')
		return (ft_strdup("$"));
	while (**endptr != '\0' && ft_isalnum(**endptr))
		(*endptr)++;
	name = ft_substr(s, 0, *endptr - s);
	if (name == NULL)
		return (NULL);
	var = getvar(ctx, name);
	free(name);
	if (var == NULL)
		return (ft_strdup(""));
	return ((char *)var->value);
}

static int	append_first_param(t_list *res, char **p,
							t_context *ctx, char quote)
{
	char	*param_value;
	char	*rest;
	t_word	*word;

	(*p)++;
	param_value = take_first_param_value(ctx, *p, &rest);
	if (param_value == NULL)
		return (EXIT_FAILURE);
	*p = rest;
	word = new_word(param_value, true, quote);
	free(param_value);
	if (word == NULL || ft_list_push_back(res, word))
	{
		destroy_word(word);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	append_scanned_word(t_list *res, char *word, char *p, char quote)
{
	char	*content;
	t_word	*scanned_word;

	content = ft_substr(word, 0, p - word);
	if (content == NULL)
		return (EXIT_FAILURE);
	scanned_word = new_word(content, false, quote);
	free(content);
	if (scanned_word == NULL)
		return (EXIT_FAILURE);
	if (ft_list_push_back(res, scanned_word) == NULL)
	{
		destroy_word(scanned_word);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	expand_parameter_helper(char *word, t_context *ctx, t_list *res)
{
	char	*p;
	char	quote;

	p = word;
	quote = '\0';
	while (*p != '\0')
	{
		if (*p == quote)
			quote = '\0';
		else if ((*p == '\'' || *p == '\"') && quote == '\0')
			quote = *p;
		if (*p == '$' && quote != '\'' && (ft_isalpha(p[1]) || p[1] == '_'))
		{
			if (append_scanned_word(res, word, p, quote))
				return (EXIT_FAILURE);
			if (append_first_param(res, &p, ctx, quote))
				return (EXIT_FAILURE);
			word = p;
			continue ;
		}
		p++;
	}
	return (EXIT_SUCCESS);
}

// Returns t_list<t_word *>
t_list	*expand_parameter(char *word, t_context *ctx)
{
	t_list	*res;

	if (word == NULL || ctx == NULL)
		return (NULL);
	res = ft_list_create();
	if (res == NULL)
		return (NULL);
	if (expand_parameter_helper(word, ctx, res))
	{
		ft_list_destroy(res, destroy_word);
		return (NULL);
	}
	return (res);
}
