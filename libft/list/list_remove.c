/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:56 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:22:57 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "list_internal.h"
#include <stdlib.h>

void	ft_list_remove(t_list *list, unsigned int index, void (*del)(void *))
{
	t_node	*node;

	node = ft_node_get(list, index);
	if (node == NULL)
		return ;
	if (node->prev == NULL)
		list->head = node->next;
	else
		node->prev->next = node->next;
	if (node->next == NULL)
		list->tail = node->prev;
	else
		node->next->prev = node->prev;
	if (del != NULL)
		del(node->data);
	free(node);
	--list->size;
}
