/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:24 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:22:26 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

t_node	*ft_node_create(void *data)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_node	*ft_node_get(t_list *list, unsigned int index)
{
	t_node	*node;

	if (list == NULL || index >= list->size)
		return (NULL);
	node = list->head;
	while (index--)
		node = node->next;
	return (node);
}

void	ft_node_remove(t_list *list, t_node *node, void (*del)(void *))
{
	if (list == NULL || node == NULL)
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
