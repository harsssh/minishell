/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:10:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/25 02:54:12 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <unistd.h>

bool	is_in_pipeline(t_pipeline_info *info)
{
	return (!(info->fd_in == STDIN_FILENO && info->fd_out == STDOUT_FILENO));
}

void	wait_children_and_set_exit_status(t_context *ctx,
		pid_t last_command_pid)
{
	int	tmp;

	tmp = wait_children(last_command_pid);
	if (tmp != -1)
		ctx->last_exit_status = tmp;
}
