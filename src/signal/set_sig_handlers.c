/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:15:48 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/15 19:15:48 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

// Sets the handlers for the shell process during input.
void	set_shell_input_sig_handlers(void)
{
	signal(SIGINT, set_sig_global_variable);
	signal(SIGQUIT, SIG_IGN);
}

// Sets the handlers for the shell process during command execution.
void	set_shell_exec_sig_handlers(void)
{
	signal(SIGINT, SIG_IGN);
}

/**
 * Sets the handlers for the process executing the command.
 * If a signal is set to be ignored in the shell process,
 * it will be ignored in the child process as well;
 * hence, this function resets the handlers to its default behavior.
 */
void	set_child_exec_sig_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
