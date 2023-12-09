/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:28:27 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/09 01:32:28 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "context.h"
#include "ft_stdio.h"
#include "init.h"
#include "utils.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

#define PROMPT "minishell$ "
#define ERR_INIT "minishell: initialization error: unable to initialize shell"

static char	*read_command_line(t_context *ctx)
{
	char	*line;

	if (ctx->is_interactive)
	{
		line = readline(PROMPT);
		if (line != NULL && *line != '\0')
			add_history(line);
	}
	else
		line = get_next_line(STDIN_FILENO);
	return (line);
}

static int	execute_command(t_context *ctx, const char *line)
{
	t_ast_node	*ast;
	int			ret;

	ast = parse(line, ctx);
	if (ast == NULL)
		return (EXIT_FAILURE);
	ret = execute_ast(ctx, ast);
	destroy_node(ast);
	return (ret);
}

static void	shell_loop(t_context *ctx)
{
	char	*line;

	while (true)
	{
		init_loop(ctx);
		line = read_command_line(ctx);
		if (line == NULL)
			break ;
		if (*line != '\0')
			execute_command(ctx, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_context	ctx;

	(void)argc;
	if (init_shell(&ctx, argv, envp) == EXIT_FAILURE)
	{
		ft_putendl_fd(ERR_INIT, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	shell_loop(&ctx);
	display_exit_message(&ctx);
	exit(ctx.last_exit_status);
}
