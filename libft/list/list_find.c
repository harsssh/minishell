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

void	*ft_list_find(t_list *list, void *ref, int (*cmp)(void *, void *))
{
	t_node	*node;

	if (list == NULL || cmp == NULL)
		return (NULL);
	node = list->head;
	while (node != NULL)
	{
		if (cmp(node->data, ref) == 0)
			return (node->data);
		node = node->next;
	}
	return (NULL);
}
