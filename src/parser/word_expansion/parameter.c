/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:40:17 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/27 00:57:56 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include "variables.h"
#include <stdlib.h>

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

static char	*join_word_param_rest(char *word, size_t word_len,
									char *param, char *rest)
{
	char	*word_cpy;
	char	*result;
	char	*tmp;

	word_cpy = ft_substr(word, 0, word_len);
	if (word_cpy == NULL)
		return (NULL);
	result = ft_strjoin(word_cpy, param);
	free(word_cpy);
	if (result == NULL)
		return (NULL);
	tmp = result;
	result = ft_strjoin(result, rest);
	free(tmp);
	return (result);
}

char	*expand_parameter(char *word, t_context *ctx)
{
	size_t		i;
	char		*param_value;
	char		*rest;
	char		*result;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			param_value = take_first_param_value(ctx, word + i + 1, &rest);
			if (param_value == NULL)
				return (NULL);
			rest = expand_parameter(rest, ctx);
			if (rest == NULL)
				return (NULL);
			result = join_word_param_rest(word, i, param_value, rest);
			free(rest);
			return (result);
		}
		i++;
	}
	return (ft_strdup(word));
}
