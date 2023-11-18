/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:07:14 by smatsuo           #+#    #+#             */
/*   Updated: 2023/11/18 18:30:11 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "variables.h"
#include "word_expansion_internal.h"

static char	*get_param_name(const char **word)
{
	const char	*p;
	char		*res;

	(*word)++;
	if (ft_strncmp(*word, "?", 1) == 0)
	{
		(*word)++;
		return (ft_strdup("?"));
	}
	p = *word;
	if (!ft_isalpha(*p) && *p != '_')
		return ("");
	while (ft_isalnum(*p) || *p == '_')
		p++;
	res = ft_substr(*word, 0, p - *word);
	if (res == NULL)
		return (NULL);
	*word = p;
	return (res);
}

static char	*get_value(char *param_name, t_context *ctx)
{
	t_variable	*var;
	char		*res;

	if (ft_strcmp(param_name, "?") == 0)
		res = ft_itoa(ctx->last_exit_status);
	else
	{
		var = getvar(ctx, param_name);
		if (var == NULL)
			res = ft_strdup("");
		else
			res = escape_string(var->value);
	}
	return (res);
}

char	*expand_first_param(const char **word, t_context *ctx)
{
	char		*param_name;
	char		*res;

	param_name = get_param_name(word);
	if (param_name == NULL)
		return (NULL);
	if (*param_name == '\0')
		return (ft_strdup("$"));
	res = get_value(param_name, ctx);
	free(param_name);
	if (res == NULL)
		return (NULL);
	return (res);
}
