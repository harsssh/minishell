/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:16:49 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 15:25:27 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_list.h"
#include <stdlib.h>
#include <sys/wait.h>

// TODO: return value when terminated by a signal
static int	wait_and_get_exit_status(pid_t pid)
{
	int	stat;

	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	return (1);
}

// TODO: if the last command is built-in?
void	wait_children(t_context *ctx, t_list *child_pid_list)
{
	pid_t	*pid_ptr;

	if (child_pid_list->size == 0)
		return ;
	while (child_pid_list->size > 1)
	{
		pid_ptr = ft_list_pop_front(child_pid_list);
		waitpid(*pid_ptr, NULL, 0);
		free(pid_ptr);
	}
	pid_ptr = ft_list_pop_front(child_pid_list);
	ctx->last_exit_status = wait_and_get_exit_status(*pid_ptr);
	free(pid_ptr);
}
