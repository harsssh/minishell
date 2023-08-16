/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:14:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/17 02:14:55 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_iter(t_list *list, void (*f)(void *))
{
	t_node	*node;

	if (list == NULL || f == NULL)
		return ;
	node = list->head;
	while (node != NULL)
	{
		f(node->data);
		node = node->next;
	}
}
