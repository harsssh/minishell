/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 02:57:58 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 02:58:15 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include "sig.h"
#include "variables.h"
#include "utils.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_PATH "/usr/local/bin:/bin:/usr/bin:."

static int	rl_hook_func(void)
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

static void	inherit_env(t_context *ctx, char **envp)
{
	char	*eq_ptr;

	while (*envp != NULL)
	{
		eq_ptr = ft_strchr(*envp, '=');
		if (eq_ptr != NULL)
		{
			*eq_ptr = '\0';
			exportvar(ctx, *envp, eq_ptr + 1);
			*eq_ptr = '=';
		}
		++envp;
	}
}

static void	init_context(t_context *ctx, char **argv, char **envp)
{
	ft_memset(ctx, 0, sizeof(t_context));
	ctx->shell_name = ft_basename(*argv);
	ctx->variables = ft_list_create();
	ctx->is_login = (**argv == '-');
	ctx->is_interactive = (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
	inherit_env(ctx, envp);
	if (getenv("PATH") == NULL)
		setvar(ctx, "PATH", DEFAULT_PATH, 1);
	if (getenv("PWD") == NULL)
	{
		bindpwd(ctx);
		exportvar(ctx, "PWD", NULL);
	}
}

void	init_shell(t_context *ctx, char **argv, char **envp)
{
	init_context(ctx, argv, envp);
	rl_outstream = stderr;
	rl_event_hook = rl_hook_func;
}

void	init_loop(t_context *ctx)
{
	set_shell_input_sig_handlers();
	if (g_sig != 0)
	{
		ctx->last_exit_status = g_sig + 128;
		g_sig = 0;
	}
}
