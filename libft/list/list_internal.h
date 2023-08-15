/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:45 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:23:19 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_INTERNAL_H
# define LIST_INTERNAL_H

# include "ft_list.h"

t_node	*ft_node_create(void *data);

t_node	*ft_node_get(t_list *list, unsigned int index);

void	ft_node_remove(t_list *list, t_node *node, void (*del)(void *));

#endif
