/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:47:30 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/29 02:11:13 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "expansion.h"
#include "ft_list.h"
#include <stdlib.h>

t_list	*expand_word_list(t_list *word_list, t_context *ctx)
{
	t_list	*new_list;
	t_list	*expanded_word;
	t_node	*node;

	if (word_list == NULL)
		return (NULL);
	new_list = ft_list_create();
	if (new_list == NULL)
		return (NULL);
	node = word_list->head;
	while (node != NULL)
	{
		expanded_word = expand_word((char *)node->data, ctx);
		if (expanded_word == NULL)
		{
			ft_list_destroy(new_list, free);
			return (NULL);
		}
		new_list = ft_list_append(new_list, expanded_word);
		node = node->next;
	}
	return (new_list);
}
