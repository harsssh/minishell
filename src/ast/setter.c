/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:59:40 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/22 17:50:51 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_list.h"
#include <stdlib.h>

int	add_node_argv(t_ast_node *node, char *arg)
{
	if (node == NULL || arg == NULL
		|| ft_list_push_back(get_node_argv(node), arg) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	add_node_redirect(t_ast_node *node, t_redirect *redirect)
{
	if (node == NULL || redirect == NULL
		|| ft_list_push_back(get_node_redirects(node), redirect) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	set_node_redirects(t_ast_node *node, t_list *redirects)
{
	node->redirects = redirects;
}
