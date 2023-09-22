/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:57:13 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/20 21:59:54 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast_node	*new_ast_node(t_ast_node_type type,
						t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (node == NULL)
	{
		destroy_node(left);
		destroy_node(right);
		return (NULL);
	}
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}
