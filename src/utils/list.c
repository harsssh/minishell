/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:12:30 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/23 04:39:01 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "utils.h"
#include <stdlib.h>

char	**list_to_string_array(t_list *list, char *(*f)(void *data))
{
	char	**array;
	char	**cur;
	t_node	*node;

	array = (char **)malloc(sizeof(char *) * (list->size + 1));
	if (array == NULL)
		return (NULL);
	cur = array;
	node = list->head;
	while (node != NULL)
	{
		if (f != NULL)
			*cur = f(node->data);
		else
			*cur = (char *)node->data;
		if (*cur == NULL)
		{
			destroy_string_array(array);
			return (NULL);
		}
		++cur;
		node = node->next;
	}
	*cur = NULL;
	return (array);
}
