/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:11:17 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 14:45:21 by kemizuki         ###   ########.fr       */
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

static void	execute_left(t_context *ctx, t_pipeline_info *info, t_ast_node *ast,
		int *fd_pipe)
{
	int	fd_out_copy;

	fd_out_copy = info->fd_out;
	info->fd_out = fd_pipe[1];
	execute_ast_impl(ctx, info, ast->left);
	info->fd_out = fd_out_copy;
}

static void	execute_right(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast, int *fd_pipe)
{
	int	fd_in_copy;

	fd_in_copy = info->fd_in;
	info->fd_in = fd_pipe[0];
	execute_ast_impl(ctx, info, ast->right);
	info->fd_in = fd_in_copy;
}

// TODO: handle error
int	handle_pipeline(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	push_fd_close_list(info, fd_pipe[0]);
	push_fd_close_list(info, fd_pipe[1]);
	execute_left(ctx, info, ast, fd_pipe);
	pop_back_and_close(info->fd_close_list);
	execute_right(ctx, info, ast, fd_pipe);
	pop_back_and_close(info->fd_close_list);
	return (EXIT_SUCCESS);
}
