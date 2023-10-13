/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:11:17 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/13 20:04:47 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_list.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

static void	pop_and_close(t_list *fd_close_list)
{
	int	*fd_ptr;

	fd_ptr = ft_list_pop_back(fd_close_list);
	if (fd_ptr == NULL)
		return ;
	close(*fd_ptr);
	free(fd_ptr);
}

static int	execute_left(t_context *ctx, t_pipeline_info *info,
	t_ast_node *ast, const int *fd_pipe)
{
	int	saved_fd_out;
	int	ret;

	saved_fd_out = info->fd_out;
	info->fd_out = fd_pipe[1];
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
	info->fd_in = fd_pipe[0];
	ret = execute_ast_impl(ctx, info, ast->right);
	info->fd_in = saved_fd_in;
	return (ret);
}

int	handle_pipeline(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	int	fd_pipe[2];
	int	result;

	if (pipe(fd_pipe) == -1)
	{
		print_simple_error(ctx, ERR_PIPE, strerror(errno));
		return (EXIT_FAILURE);
	}
	push_fd_close_list(info, fd_pipe[0]);
	result = execute_right(ctx, info, ast, fd_pipe);
	pop_and_close(info->fd_close_list);
	pop_and_close(info->fd_close_list);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	push_fd_close_list(info, fd_pipe[1]);
	result = execute_left(ctx, info, ast, fd_pipe);
	pop_and_close(info->fd_close_list);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
