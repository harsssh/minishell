/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:21:03 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 07:21:46 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stddef.h>

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_list
{
	t_node			*head;
	t_node			*tail;
	size_t			size;
}					t_list;

t_list	*ft_list_create(void);
void	ft_list_destroy(t_list *list, void (*del)(void *));

void	*ft_list_get(t_list *list, unsigned int index);

void	ft_list_push_front(t_list *list, void *data);
void	ft_list_push_back(t_list *list, void *data);
void	ft_list_insert(t_list *list, unsigned int index, void *data);

void	*ft_list_pop_front(t_list *list);
void	*ft_list_pop_back(t_list *list);
void	ft_list_remove(t_list *list, unsigned int index, void (*del)(void *));
void	ft_list_clear(t_list *list, void (*del)(void *));

#endif
