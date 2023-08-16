/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:08:52 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 19:09:19 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

static int	push_back_copy(t_list *list, void *data, void *(*cpy)(void *data))
{
	void	*new_data;
	size_t	prev_size;

	new_data = cpy(data);
	if (new_data == NULL)
		return (-1);
	prev_size = list->size;
	ft_list_push_back(list, new_data);
	if (prev_size == list->size)
	{
		free(new_data);
		return (-1);
	}
	return (0);
}

// Using the 'cpy' function is essential
// to prevent potential double freeing of the same data
t_list	*ft_list_copy(t_list *list, void *(*cpy)(void *data),
		void (*del)(void *data))
{
	t_list	*new_list;
	t_node	*node;

	if (list == NULL || cpy == NULL)
		return (NULL);
	new_list = ft_list_create();
	if (new_list == NULL)
		return (NULL);
	node = list->head;
	while (node != NULL)
	{
		if (push_back_copy(new_list, node->data, cpy) == -1)
		{
			ft_list_destroy(new_list, del);
			return (NULL);
		}
		node = node->next;
	}
	return (new_list);
}
