/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:57:53 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/03 19:16:30 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "libft.h"
#include "context.h"
#include "word_expansion_internal.h"

// char * -> t_list<char *>
t_list	*expand_word(const char *word, t_context *ctx)
{
	t_list				*res;
	t_list				*tmp;

	res = expand_parameters(word, ctx, NOT_EXPAND_IN_SINGLE_QUOTE);
	if (res == NULL)
		return (NULL);
	tmp = res;
	if (ft_strchr(word, '=') == NULL)
	{
		res = split_word(res);
		ft_list_destroy(tmp, free);
		if (res == NULL)
			return (NULL);
		tmp = res;
		res = expand_filenames(res);
		ft_list_destroy(tmp, free);
		if (res == NULL)
			return (NULL);
		tmp = res;
	}
	res = remove_quotes(res);
	ft_list_destroy(tmp, free);
	return (res);
}
