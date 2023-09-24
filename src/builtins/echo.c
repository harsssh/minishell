/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:17:25 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/16 00:44:23 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins_internal.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static char	**skip_options(char **args, bool *newline)
{
	char	*str;

	*newline = true;
	while (args && *args && **args == '-')
	{
		str = *args;
		while (*(++str) == 'n')
			;
		if ((*args)[1] == '\0' || *str != '\0')
			break ;
		*newline = false;
		++args;
	}
	return (args);
}

static void	print_args(char **args, bool newline)
{
	while (args && *args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		++args;
		if (*args)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	builtins_echo(t_context *ctx, char **args)
{
	bool	newline;

	args = skip_options(args, &newline);
	errno = 0;
	print_args(args, newline);
	if (errno)
	{
		perror_verbose(ctx, "echo", ERR_WRITE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
