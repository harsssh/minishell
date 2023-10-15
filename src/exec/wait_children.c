/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:16:49 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/15 21:19:33 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// NOTE: bash does not display the message for SIGINT
static void	report_signal_termination(int sig)
{
	const char	*message;

	if (sig == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else
	{
		if (sig <= 0 || sig >= NSIG)
			message = "Unknown signal";
		else
			message = sys_siglist[sig];
		ft_dprintf(STDERR_FILENO, "%s: %d\n", message, sig);
	}
}

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
	int		target_term_sig;
	int		target_exit_status;
	pid_t	waited_pid;

	target_term_sig = -1;
	target_exit_status = -1;
	errno = 0;
	waited_pid = wait3(&stat, WNOHANG, NULL);
	while (errno != ECHILD)
	{
		if (waited_pid == target_pid)
		{
			target_exit_status = get_exit_status(stat);
			if (WIFSIGNALED(stat))
				target_term_sig = WTERMSIG(stat);
		}
		waited_pid = wait3(&stat, WNOHANG, NULL);
	}
	if (target_term_sig != -1)
		report_signal_termination(target_term_sig);
	return (target_exit_status);
}
