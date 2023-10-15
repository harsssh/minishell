/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:16:49 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/25 02:54:03 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "ft_list.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

static int	get_exit_status(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (WTERMSIG(stat) + 128);
	else
		return (EXIT_FAILURE);
}

// NOTE: bash also loops infinitely if wait fails
// returns exit status of the specified process, or -1 if not found
int	wait_children(pid_t target_pid)
{
	int		stat;
	int		exit_status;
	pid_t	waited_pid;

	errno = 0;
	exit_status = -1;
	waited_pid = wait3(&stat, WNOHANG, NULL);
	while (errno != ECHILD)
	{
		if (waited_pid == target_pid)
			exit_status = get_exit_status(stat);
		waited_pid = wait3(&stat, WNOHANG, NULL);
	}
	return (exit_status);
}
