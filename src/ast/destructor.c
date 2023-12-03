/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:57:55 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/03 16:53:18 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

void	destroy_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	if (redirect->type == REDIRECT_HERE_DOC)
		unlink(redirect->filename);
	free(redirect->filename);
	free(redirect);
}

void	destroy_node(t_ast_node *node)
{
	if (node == NULL)
		return ;
	destroy_node(node->left);
	destroy_node(node->right);
	ft_list_destroy(node->argv, free);
	ft_list_destroy(node->redirects, (void (*)(void *data))destroy_redirect);
	free(node);
}
