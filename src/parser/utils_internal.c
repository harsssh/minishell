/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:08:34 by kemizuki          #+#    #+#             */
/*   Updated: 2023/12/02 23:44:41 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	*destroy_nodes_and_return_null(t_ast_node *n1, t_ast_node *n2)
{
	destroy_node(n1);
	destroy_node(n2);
	return (NULL);
}

void	*destroy_redirect_and_return_null(t_redirect *redirect)
{
	destroy_redirect(redirect);
	return (NULL);
}
