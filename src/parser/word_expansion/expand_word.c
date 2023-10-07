/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:05:26 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/27 03:44:09 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include "variables.h"
#include <stdlib.h>
#include "word_expansion_internal.h"

char	*expand_word(char *word, t_context *ctx)
{
	if (word == NULL)
		return (NULL);
	word = expand_parameter(word, ctx);
	if (word == NULL)
		return (NULL);
//	tmp = word;
//	word = split_fields(new_word);
//	free(tmp);
//	if (word == NULL)
//		return (NULL);
//	tmp = word;
//	word = remove_quotes(new_word);
//	free(tmp);
	return (word);
}