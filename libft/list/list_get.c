/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:39 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:22:40 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "list_internal.h"

void	*ft_list_get(t_list *list, unsigned int index)
{
	t_node	*node;

	node = ft_node_get(list, index);
	if (node == NULL)
		return (NULL);
	return (node->data);
}
