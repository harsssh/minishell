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

void	ft_list_insert(t_list *list, unsigned int index, void *data)
{
	t_node	*new;
	t_node	*node;

	if (list == NULL)
		return ;
	if (index == 0)
	{
		ft_list_push_front(list, data);
		return ;
	}
	if (index >= list->size)
	{
		ft_list_push_back(list, data);
		return ;
	}
	new = ft_node_create(data);
	if (new == NULL)
		return ;
	node = ft_node_get(list, index);
	new->next = node;
	new->prev = node->prev;
	node->prev->next = new;
	node->prev = new;
	++list->size;
}
