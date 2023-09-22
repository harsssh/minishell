/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:59:40 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/20 22:12:44 by smatsuo          ###   ########.fr       */
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
	return (EXIT_SUCCESS)
}
