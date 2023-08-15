/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exclude.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:20:30 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 18:20:47 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "list_internal.h"

void	ft_list_exclude(t_list *list, void *ref, int (*cmp)(void *, void *),
		void (*del)(void *))
{
	t_node	*node;
	t_node	*next;

	if (list == NULL || cmp == NULL)
		return ;
	node = list->head;
	while (node != NULL)
	{
		next = node->next;
		if (cmp(node->data, ref) != 0)
			ft_node_remove(list, node, del);
		node = next;
	}
}
