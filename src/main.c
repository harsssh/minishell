/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:28:27 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/17 17:23:29 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "context.h"
#include "parser.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define PROMPT "minishell$ "

void		init_shell(t_context *ctx, char **argv, char **envp);
void		init_loop(t_context *ctx);

static void	display_exit_message(t_context *ctx)
{
	if (ctx->is_interactive)
	{
		if (ctx->is_login)
			ft_putendl_fd("logout", STDERR_FILENO);
		else
			ft_putendl_fd("exit", STDERR_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_context	ctx;
	t_ast_node	*ast;

	(void)argc;
	init_shell(&ctx, argv, envp);
	while (true)
	{
		init_loop(&ctx);
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			ast = parse(line, &ctx);
			if (ast != NULL)
				execute_ast(&ctx, ast);
			destroy_node(ast);
		}
		free(line);
	}
	display_exit_message(&ctx);
	exit(ctx.last_exit_status);
}
