/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:21:03 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 23:48:04 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stddef.h>
# include <stdbool.h>

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
t_list	*ft_list_copy(t_list *list, void *(*cpy)(void *data),
			void (*del)(void *data));
void	ft_list_destroy(t_list *list, void (*del)(void *data));

// Creates a new list by including only elements
// for which the 'pred' function returns true,
// without modifying the original list
t_list	*ft_list_filter(t_list *list, bool (*pred)(void *data),
			void *(*cpy)(void *data), void (*del)(void *data));
// Creates a new list by excluding elements
// for which the 'pred' function returns true,
// without modifying the original list
t_list	*ft_list_exclude(t_list *list, bool (*pred)(void *data),
			void *(*cpy)(void *data), void (*del)(void *data));

// Searches for an element that satisfies the condition
void	*ft_list_find(t_list *list, void *ref,
			bool (*pred)(void *data, void *ref));

t_node	*ft_list_push_front(t_list *list, void *data);
t_node	*ft_list_push_back(t_list *list, void *data);
// Inserts a new node containing the provided data
// before the specified position
void	ft_list_insert(t_list *list, t_node *pos, void *data);

void	*ft_list_pop_front(t_list *list);
void	*ft_list_pop_back(t_list *list);
// Removes the node at the specified position,
// invoking the provided 'del' function
void	ft_list_remove(t_list *list, t_node *pos, void (*del)(void *data));
// Removes all elements that satisfy the condition
// invoking the provided 'del' function for each removed element.
void	ft_list_remove_if(t_list *list, void *ref,
			bool (*pred)(void *data, void *ref), void (*del)(void *data));
void	ft_list_clear(t_list *list, void (*del)(void *));

void	ft_list_iter(t_list *list, void (*f)(void *data));
void	ft_list_iter_enumerate(t_list *list, void (*f)(size_t i, void *data));

t_list	*ft_list_append(t_list *l1, t_list *l2);

#endif
