/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:03:34 by kemizuki          #+#    #+#             */
/*   Updated: 2023/12/09 09:24:57 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "init.h"
#include "init_internal.h"
#include "libft.h"
#include "sig.h"
#include "utils.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#define DEFAULT_PATH		"/usr/local/bin:/bin:/usr/bin:."
#define DEFAULT_SHELL_NAME	"minishell"

static int	set_default_values(t_context *ctx)
{
	if (getenv("PATH") == NULL)
	{
		if (setvar(ctx, "PATH", DEFAULT_PATH, 1) == -1)
			return (EXIT_FAILURE);
	}
	if (getenv("PWD") == NULL)
	{
		if (bindpwd(ctx, "shell-init") == EXIT_SUCCESS)
		{
			if (exportvar(ctx, "PWD", NULL) == -1)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	destroy_and_return_failure(t_context *ctx)
{
	free((void *)ctx->shell_name);
	ft_list_destroy(ctx->variables, free);
	return (EXIT_FAILURE);
}

static int	init_context(t_context *ctx, char **argv, char **envp)
{
	ft_memset(ctx, 0, sizeof(t_context));
	if (**argv == '\0' || ft_strcmp(*argv, "-") == 0)
		ctx->shell_name = ft_strdup(DEFAULT_SHELL_NAME);
	else
		ctx->shell_name = ft_basename(*argv);
	if (ctx->shell_name == NULL)
		return (destroy_and_return_failure(ctx));
	ctx->variables = ft_list_create();
	if (ctx->variables == NULL)
		return (destroy_and_return_failure(ctx));
	ctx->is_login = (**argv == '-');
	ctx->is_interactive = (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
	if (inherit_env(ctx, envp) == EXIT_FAILURE)
		return (destroy_and_return_failure(ctx));
	if (set_default_values(ctx) == EXIT_FAILURE)
		return (destroy_and_return_failure(ctx));
	return (EXIT_SUCCESS);
}

int	init_shell(t_context *ctx, char **argv, char **envp)
{
	if (init_context(ctx, argv, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ctx->is_interactive)
	{
		rl_outstream = stderr;
		rl_event_hook = sigint_event_hook;
	}
	return (EXIT_SUCCESS);
}
