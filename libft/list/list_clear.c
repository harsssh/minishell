/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:29 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:22:30 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

void	ft_list_clear(t_list *list, void (*del)(void *))
{
	t_node	*node;
	t_node	*next;

	if (list == NULL)
		return ;
	node = list->head;
	while (node != NULL)
	{
		next = node->next;
		if (del != NULL)
			del(node->data);
		free(node);
		node = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}
