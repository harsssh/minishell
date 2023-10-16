/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_node_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:19:55 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/09 22:21:12 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include <stdlib.h>

int	append_node_argv(t_ast_node *node, t_list *words)
{
	t_node	*cur;
	char	*word;

	if (node == NULL || words == NULL)
		return (EXIT_FAILURE);
	cur = words->head;
	while (cur != NULL)
	{
		word = (char *)cur->data;
		if (word == NULL)
			return (EXIT_FAILURE);
		if (add_node_argv(node, word))
			return (EXIT_FAILURE);
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}
