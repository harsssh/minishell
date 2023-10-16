/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:12:49 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/25 14:12:32 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_list	*get_node_argv(t_ast_node *node)
{
	return (node->argv);
}

t_list	*get_node_redirects(t_ast_node *node)
{
	return (node->redirects);
}
