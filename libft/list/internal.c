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
