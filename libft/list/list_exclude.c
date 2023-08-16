/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exclude.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:20:30 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 19:08:46 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_exclude(t_list *list, bool (*pred)(void *data),
		void *(*cpy)(void *data), void (*del)(void *data))
{
	t_list	*new_list;
	t_node	*node;
	t_node	*next;

	if (list == NULL || pred == NULL || cpy == NULL)
		return (NULL);
	new_list = ft_list_copy(list, cpy, del);
	if (new_list == NULL)
		return (NULL);
	node = new_list->head;
	while (node != NULL)
	{
		next = node->next;
		if (pred(node->data))
			ft_list_remove(new_list, node, del);
		node = next;
	}
	return (new_list);
}
