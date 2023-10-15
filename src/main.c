/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:31:46 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 02:58:44 by kemizuki         ###   ########.fr       */
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

#define PROMPT "minishell$ "

void	init_shell(t_context *ctx, char **argv, char **envp);
void	init_loop(t_context *ctx);

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_context	ctx;

	(void)argc;
	init_shell(&ctx, argv, envp);
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
