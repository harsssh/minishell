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

#include "ast.h"
#include "context.h"
#include "sig.h"
#include "variables.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

#define PROMPT "minishell$ "

int	rl_hook_func(void)
{
	if (g_sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = true;
	}
	return (EXIT_SUCCESS);
}

static void	init_loop(t_context *ctx)
{
	set_shell_input_sig_handlers();
	if (g_sig != 0)
	{
		ctx->last_exit_status = g_sig + 128;
		g_sig = 0;
	}
}

static void	init_shell(t_context *ctx, const char *cmd_name)
{
	ft_memset(ctx, 0, sizeof(t_context));
	ctx->shell_name = ft_basename(cmd_name);
	ctx->variables = ft_list_create();
	ctx->is_login = (cmd_name[0] == '-');
	ctx->is_interactive = (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
	exportvar(ctx, "PATH", "/bin:/usr/bin");
	rl_outstream = stderr;
	rl_event_hook = rl_hook_func;
}

int	main(int argc, char **argv)
{
	char		*line;
	t_context	ctx;

	(void)argc;
	init_shell(&ctx, argv[0]);
	while (true)
	{
		init_loop(&ctx);
		line = readline(PROMPT);
		if (line == NULL)
			exit(EXIT_SUCCESS);
		if (*line != '\0')
			add_history(line);
		free(line);
	}
}
