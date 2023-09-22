/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 14:39:41 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "context.h"
#include "exec_internal.h"
#include "ft_list.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define PERM_RW 0666

static void	close_iter_fn(void *data)
{
	int	*fd_ptr;

	fd_ptr = data;
	close(*fd_ptr);
}

static int	open_for_redirect(t_redirect *redirect)
{
	int	fd;

	if (redirect->type == REDIRECT_IN || redirect->type == REDIRECT_HERE_DOC)
		fd = open(redirect->filename, O_RDONLY);
	else if (redirect->type == REDIRECT_OUT)
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, PERM_RW);
	else if (redirect->type == REDIRECT_APPEND)
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, PERM_RW);
	else
		return (-1);
	return (fd);
}

static void	set_redirect_iter_fn(void *data)
{
	int			fd_target;
	int			fd_redirect;
	t_redirect	*redirect;

	redirect = (t_redirect *)data;
	fd_redirect = open_for_redirect(redirect);
	if (fd_redirect == -1)
		return ;
	if (redirect->type == REDIRECT_IN || redirect->type == REDIRECT_HERE_DOC)
		fd_target = STDIN_FILENO;
	else if (redirect->type == REDIRECT_OUT | redirect->type == REDIRECT_APPEND)
		fd_target = STDIN_FILENO;
	else
		return ;
	dup2(fd_redirect, fd_target);
	close(fd_redirect);
}

// for child process
static void	configure_io(t_list *redirect_list, t_pipeline_info *info)
{
	if (info->fd_in != STDIN_FILENO)
		dup2(info->fd_in, STDIN_FILENO);
	if (info->fd_out != STDOUT_FILENO)
		dup2(info->fd_out, STDOUT_FILENO);
	ft_list_iter(info->fd_close_list, close_iter_fn);
	ft_list_iter(redirect_list, set_redirect_iter_fn);
}

int	handle_command(t_context *ctx, t_pipeline_info *info, t_ast_node *ast)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		configure_io(ast->redirects, info);
		internal_execvp(ctx, ast->argv);
		exit(EXIT_FAILURE);
	}
	push_child_pid_list(info, pid);
	if (!is_in_pipeline(info))
		wait_children(ctx, info->child_pid_list);
	return (EXIT_SUCCESS);
}
