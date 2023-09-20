/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/21 00:10:49 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>
#include <unistd.h>

static void	close_iter_fn(void *data)
{
	int	*fd_ptr;

	fd_ptr = data;
	close(*fd_ptr);
}

// for child process
static void	configure_io(t_pipeline_info *info)
{
	if (info->fd_in != STDIN_FILENO)
	{
		dup2(info->fd_in, STDIN_FILENO);
		close(info->fd_in);
	}
	if (info->fd_out != STDOUT_FILENO)
	{
		dup2(info->fd_out, STDOUT_FILENO);
		close(info->fd_out);
	}
	ft_list_iter(info->fd_close_list, close_iter_fn);
}

static int	child_routine(t_context *ctx, t_pipeline_info *info,
		t_ast_node *ast)
{
	(void)ctx;
	(void)ast;
	configure_io(info);
	return (0);
}

int	handle_command(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		child_routine(ctx, info, ast);
		exit(EXIT_FAILURE);
	}
	return (0);
}
