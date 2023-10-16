/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:17:25 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 13:53:01 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_internal.h"
#include "libft.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static const char	**load_options(const char **args, bool *newline)
{
	t_getopt_status	status;
	char			c;

	*newline = true;
	init_get_next_option();
	while (*args)
	{
		status = get_next_option(*args, "n", &c);
		while (status == OPT_SUCCESS)
		{
			if (c == 'n')
				*newline = false;
			status = get_next_option(NULL, "n", &c);
		}
		if (status == OPT_ILLEGAL)
			*newline = true;
		if (status != OPT_END_OF_ARG)
			break ;
		++args;
	}
	return (args);
}

static void	print_args(const char **args, bool newline)
{
	while (*args)
	{
		ft_putstr_fd((char *)(*args), STDOUT_FILENO);
		++args;
		if (*args)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	builtins_echo(t_context *ctx, const char **args)
{
	bool	newline;

	args = load_options(args, &newline);
	errno = 0;
	print_args(args, newline);
	if (errno)
	{
		perror_verbose(ctx, "echo", ERR_WRITE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
