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

static const char	**skip_options(const char **argv, bool *newline)
{
	const char	*str;

	*newline = true;
	while (argv && *argv && **argv == '-')
	{
		str = *argv;
		while (*(++str) == 'n')
			;
		if ((*argv)[1] == '\0' || *str != '\0')
			break ;
		*newline = false;
		++argv;
	}
	return (argv);
}

static void	print_args(const char **argv, bool newline)
{
	while (argv && *argv)
	{
		ft_putstr_fd((char *)*argv, STDOUT_FILENO);
		++argv;
		if (*argv)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	builtins_echo(t_context *ctx, const char **argv)
{
	bool	newline;

	argv = skip_options(argv, &newline);
	errno = 0;
	print_args(argv, newline);
	if (errno)
	{
		perror_builtin(ctx, "echo", ERR_WRITE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
