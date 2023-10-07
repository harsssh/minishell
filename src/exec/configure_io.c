/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:26:39 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/25 04:57:11 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "utils.h"
#include <fcntl.h>
#include <stdlib.h>

static void	close_iter_fn(void *data)
{
	int	*fd_ptr;

	fd_ptr = data;
	close(*fd_ptr);
}

static int	open_for_redirect(t_context *ctx, t_redirect *redirect)
{
	int	fd;

	if (redirect->filename == NULL)
	{
		print_simple_error(ctx, ERR_AMBIGUOUS_REDIRECT, strerror(errno));
		return (-1);
	}
	if (redirect->type == REDIRECT_IN || redirect->type == REDIRECT_HERE_DOC)
		fd = open(redirect->filename, O_RDONLY);
	else if (redirect->type == REDIRECT_OUT)
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redirect->type == REDIRECT_APPEND)
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		return (-1);
	if (fd == -1)
		print_simple_error(ctx, redirect->filename, strerror(errno));
	return (fd);
}

// TODO?: handle dup2 error
static int	configure_redirect(t_context *ctx, t_list *redirects)
{
	int			fd_redirect;
	t_node		*node;
	t_redirect	*redirect;

	if (redirects == NULL)
		return (EXIT_SUCCESS);
	node = redirects->head;
	while (node != NULL)
	{
		redirect = (t_redirect *)node->data;
		fd_redirect = open_for_redirect(ctx, redirect);
		if (fd_redirect == -1)
			return (EXIT_FAILURE);
		if (redirect->type == REDIRECT_IN
			|| redirect->type == REDIRECT_HERE_DOC)
			dup2(fd_redirect, STDIN_FILENO);
		else
			dup2(fd_redirect, STDOUT_FILENO);
		close(fd_redirect);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

// for child process
int	configure_io(t_context *ctx, t_pipeline_info *info, t_list *redirect_list)
{
	if (info->fd_in != STDIN_FILENO)
		dup2(info->fd_in, STDIN_FILENO);
	if (info->fd_out != STDOUT_FILENO)
		dup2(info->fd_out, STDOUT_FILENO);
	ft_list_iter(info->fd_close_list, close_iter_fn);
	if (configure_redirect(ctx, redirect_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
