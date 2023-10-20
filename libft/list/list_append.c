/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:33:15 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 23:50:09 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

t_list	*ft_list_append(t_list *l1, t_list *l2)
{
	if (l1 == NULL || l2 == NULL)
		return (l1);
	if (l1->size == 0)
	{
		*l1 = *l2;
		free(l2);
		return (l1);
	}
	if (l2->size == 0)
	{
		free(l2);
		return (l1);
	}
	l1->tail->next = l2->head;
	l2->head->prev = l1->tail;
	l1->tail = l2->tail;
	l1->size += l2->size;
	free(l2);
	return (l1);
}
