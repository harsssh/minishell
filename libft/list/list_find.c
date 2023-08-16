/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 08:49:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 08:49:57 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	*ft_list_find(t_list *list, void *ref, bool (*pred)(void *, void *))
{
	t_node	*node;

	if (list == NULL || pred == NULL)
		return (NULL);
	node = list->head;
	while (node != NULL)
	{
		if (pred(node->data, ref))
			return (node->data);
		node = node->next;
	}
	return (NULL);
}
