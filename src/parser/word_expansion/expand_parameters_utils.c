/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:07:14 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/19 18:17:23 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "variables.h"

static char	*get_param_name(char **word)
{
	char	*p;
	char	*res;

	(*word)++;
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

char	*expand_first_param(char **word, t_context *ctx)
{
	char		*param_name;
	t_variable	*var;
	char		*res;

	param_name = get_param_name(word);
	if (param_name == NULL)
		return (NULL);
	if (*param_name == '\0')
		return (ft_strdup("$"));
	var = getvar(ctx, param_name);
	free(param_name);
	if (var == NULL)
		return (ft_strdup(""));
	res = ft_strdup(var->value);
	if (res == NULL)
		return (NULL);
	return (res);
}
