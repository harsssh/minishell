/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:28:27 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 22:28:40 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

#define PROMPT "minishell$ "

volatile sig_atomic_t	g_sig;

void	sigint_handler(int sig)
{
	g_sig = sig;
}

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

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_outstream = stderr;
	rl_event_hook = rl_hook_func;
	while (true)
	{
		line = readline(PROMPT);
		if (line == NULL)
			exit(EXIT_SUCCESS);
		if (*line != '\0')
			add_history(line);
		free(line);
	}
}
