/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:11:17 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/14 14:08:13 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_list.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

#define IDX_PIPE_OUT 0
#define IDX_PIPE_IN 1

// if the list is empty, -1 is popped
static void	pop_and_close(t_list *fd_close_list)
{
	int	fd;

	fd = pop_fd_close_list(fd_close_list);
	if (fd != -1)
		close(fd);
}

static int	execute_left(t_context *ctx, t_pipeline_info *info, t_ast_node *ast,
		const int *fd_pipe)
{
	int	saved_fd_out;
	int	ret;

	saved_fd_out = info->fd_out;
	info->fd_out = fd_pipe[IDX_PIPE_IN];
	ret = execute_ast_impl(ctx, info, ast->left);
	info->fd_out = saved_fd_out;
	return (ret);
}

static int	execute_right(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast, const int *fd_pipe)
{
	int	saved_fd_in;
	int	ret;

	saved_fd_in = info->fd_in;
	info->fd_in = fd_pipe[IDX_PIPE_OUT];
	ret = execute_ast_impl(ctx, info, ast->right);
	info->fd_in = saved_fd_in;
	return (ret);
}

/*
 * - Closes unnecessary fds immediately.
 * - Minimizes open fds by executing the right AST subtree first.
 * - Right subtree: Leaf nodes should close both ends of the new left pipe
     and left end of right pipe.
 * - Left subtree: Leaf nodes should close left end of the new right pipe.
 */
int	handle_pipeline(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	int	fd_pipe[2];
	int	result;

	if (pipe(fd_pipe) == -1)
	{
		print_simple_error(ctx, ERR_PIPE, strerror(errno));
		return (EXIT_FAILURE);
	}
	push_fd_close_list(info->fd_close_list, fd_pipe[IDX_PIPE_OUT]);
	push_fd_close_list(info->fd_close_list, fd_pipe[IDX_PIPE_IN]);
	result = execute_right(ctx, info, ast, fd_pipe);
	pop_fd_close_list(info->fd_close_list);
	pop_and_close(info->fd_close_list);
	pop_and_close(info->fd_close_list);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	push_fd_close_list(info->fd_close_list, fd_pipe[IDX_PIPE_IN]);
	result = execute_left(ctx, info, ast, fd_pipe);
	pop_and_close(info->fd_close_list);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
