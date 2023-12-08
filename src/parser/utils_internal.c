/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:08:34 by kemizuki          #+#    #+#             */
/*   Updated: 2023/12/08 20:52:53 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <readline/readline.h>
#include "context.h"
#include <unistd.h>
#include <stdlib.h>

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

char	*read_command_line(t_context *ctx)
{
	char	*line;
	char	*tmp;

	if (ctx->is_interactive)
		line = readline("> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (NULL);
		tmp = line;
		line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	return (line);
}
