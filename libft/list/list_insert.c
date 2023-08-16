/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:42 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:22:43 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "list_internal.h"

void	ft_list_insert(t_list *list, t_node *pos, void *data)
{
	t_node	*node;

	if (list == NULL || pos == NULL)
		return ;
	node = ft_node_create(data);
	if (node == NULL)
		return ;
	node->prev = pos->prev;
	node->next = pos;
	if (pos->prev != NULL)
		pos->prev->next = node;
	pos->prev = node;
	if (list->head == pos)
		list->head = node;
	++list->size;
}
