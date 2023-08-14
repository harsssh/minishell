/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:52 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:22:54 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "list_internal.h"

void	ft_list_push_front(t_list *list, void *data)
{
	t_node	*node;

	if (list == NULL)
		return ;
	node = ft_node_create(data);
	if (node == NULL)
		return ;
	node->next = list->head;
	if (list->head != NULL)
		list->head->prev = node;
	list->head = node;
	if (list->tail == NULL)
		list->tail = node;
	++list->size;
}

void	ft_list_push_back(t_list *list, void *data)
{
	t_node	*node;

	if (list == NULL)
		return ;
	node = ft_node_create(data);
	if (node == NULL)
		return ;
	node->prev = list->tail;
	if (list->tail != NULL)
		list->tail->next = node;
	list->tail = node;
	if (list->head == NULL)
		list->head = node;
	++list->size;
}
