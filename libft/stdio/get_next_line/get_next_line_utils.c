/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:22:34 by kemizuki          #+#    #+#             */
/*   Updated: 2023/06/01 17:36:55 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

// create a new node and add it to the head of the list
// the return value is the created node
t_buffer_list	*push_front_new_node(t_buffer_list **list, int fd)
{
	t_buffer		*buf;
	t_buffer_list	*node;

	if (list == NULL)
		return (NULL);
	buf = malloc(sizeof(t_buffer));
	if (buf == NULL)
		return (NULL);
	buf->fd = fd;
	buf->len = 0;
	buf->read_failed = false;
	node = malloc(sizeof(t_buffer_list));
	if (node == NULL)
	{
		free(buf);
		return (NULL);
	}
	node->buf = buf;
	node->next = *list;
	node->prev = NULL;
	if (*list != NULL)
		(*list)->prev = node;
	*list = node;
	return (node);
}

void	remove_node(t_buffer_list **list, int fd)
{
	t_buffer_list	*node;

	if (list == NULL)
		return ;
	node = *list;
	while (node != NULL && node->buf->fd != fd)
		node = node->next;
	if (node == NULL)
		return ;
	if (node->prev != NULL)
		node->prev->next = node->next;
	else
		*list = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	free(node->buf);
	free(node);
}
