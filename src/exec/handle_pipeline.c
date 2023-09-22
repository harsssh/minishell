/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:11:17 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 13:38:51 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

static void	pop_back_and_close(t_list *fd_close_list)
{
	pid_t	*pid_ptr;

	pid_ptr = ft_list_pop_back(fd_close_list);
	close(*pid_ptr);
	free(pid_ptr);
}

// TODO: handle error
int	handle_pipeline(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	int	fd[2];

	pipe(fd);
	push_fd_close_list(info, fd[0]);
	push_fd_close_list(info, fd[1]);
	execute_ast_impl(ctx, info, ast->left);
	pop_back_and_close(info->fd_close_list);
	execute_ast_impl(ctx, info, ast->right);
	pop_back_and_close(info->fd_close_list);
	return (EXIT_SUCCESS);
}
