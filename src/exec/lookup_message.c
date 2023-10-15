/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:33:29 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/15 21:19:26 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

static void	set_lookup_table_entry(const char **table);
static void	set_lookup_table_entry2(const char **table);

// TODO: stop initializing the table every time
const char	*lookup_termination_message(int sig)
{
	static const char	*lookup_table[NSIG];

	if (sig <= 0 || sig >= NSIG)
		return ("Unknown signal");
	set_lookup_table_entry(lookup_table);
	return (lookup_table[sig]);
}

// WARNING: This function is not portable.
static void	set_lookup_table_entry(const char **table)
{
	table[SIGHUP] = "Hangup";
	table[SIGINT] = "Interrupt";
	table[SIGQUIT] = "Quit";
	table[SIGILL] = "Illegal instruction";
	table[SIGTRAP] = "BPT trace/trap";
	table[SIGABRT] = "ABORT instruction";
	table[SIGEMT] = "EMT instruction";
	table[SIGFPE] = "Floating point exception";
	table[SIGKILL] = "Killed";
	table[SIGBUS] = "Bus error";
	table[SIGSEGV] = "Segmentation fault";
	table[SIGSYS] = "Bad system call";
	table[SIGPIPE] = "Broken pipe";
	table[SIGALRM] = "Alarm clock";
	table[SIGTERM] = "Terminated";
	table[SIGURG] = "Urgent IO condition";
	table[SIGSTOP] = "Stopped (signal)";
	table[SIGTSTP] = "Stopped";
	table[SIGCONT] = "Continue";
	table[SIGCHLD] = "Child death or stop";
	table[SIGTTIN] = "Stopped (tty input)";
	table[SIGTTOU] = "Stopped (tty output)";
	table[SIGIO] = "I/O ready";
	table[SIGXCPU] = "CPU limit";
	set_lookup_table_entry2(table);
}

// WARNING: This function is not portable.
static void	set_lookup_table_entry2(const char **table)
{
	table[SIGXFSZ] = "File limit";
	table[SIGVTALRM] = "Alarm (virtual)";
	table[SIGPROF] = "Alarm (profile)";
	table[SIGWINCH] = "Window changed";
	table[SIGINFO] = "Information request";
	table[SIGUSR1] = "User signal 1";
	table[SIGUSR2] = "User signal 2";
}
