/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:56 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 19:09:39 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

void	ft_list_remove(t_list *list, t_node *pos, void (*del)(void *data))
{
	if (list == NULL || pos == NULL)
		return ;
	if (pos->prev == NULL)
		list->head = pos->next;
	else
		pos->prev->next = pos->next;
	if (pos->next == NULL)
		list->tail = pos->prev;
	else
		pos->next->prev = pos->prev;
	if (del != NULL)
		del(pos->data);
	free(pos);
	--list->size;
}

void	ft_list_remove_if(t_list *list, void *ref, bool (*pred)(void *data,
			void *ref), void (*del)(void *data))
{
	t_node	*node;
	t_node	*next;

	if (list == NULL || pred == NULL)
		return ;
	node = list->head;
	while (node != NULL)
	{
		next = node->next;
		if (pred(node->data, ref))
			ft_list_remove(list, node, del);
		node = next;
	}
}
