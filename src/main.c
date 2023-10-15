/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:03:58 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/30 15:49:25 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>
#include "context.h"
#include "sig.h"

#define PROMPT "minishell$ "

int	rl_hook_func(void)
{
	if (g_sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 0;
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	rl_event_hook = rl_hook_func;
	while (true)
	{
		set_shell_input_sig_handlers();
		line = readline(PROMPT);
		if (line == NULL)
			exit(EXIT_SUCCESS);
		if (*line != '\0')
			add_history(line);
		free(line);
	}
}
