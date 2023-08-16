/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:22:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 08:22:53 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	*ft_list_pop_front(t_list *list)
{
	void	*data;

	if (list == NULL)
		return (NULL);
	if (list->head == NULL)
		return (NULL);
	data = list->head->data;
	ft_list_remove(list, list->head, NULL);
	return (data);
}

void	*ft_list_pop_back(t_list *list)
{
	void	*data;

	if (list == NULL)
		return (NULL);
	if (list->tail == NULL)
		return (NULL);
	data = list->tail->data;
	ft_list_remove(list, list->tail, NULL);
	return (data);
}
