/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:17:25 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/11 15:47:49 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool	is_option(char *arg)
{
	unsigned int	count;

	if (*arg != '-')
		return (false);
	arg++;
	count = 0;
	while (*arg)
	{
		if (*arg != 'n')
			return (false);
		arg++;
		count++;
	}
	return (count > 0);
}

static unsigned int	count_option(int argc, char **argv)
{
	unsigned int	i;
	unsigned int	count;

	i = 1;
	count = 0;
	while (i < (unsigned int)argc)
	{
		if (!is_option(argv[i]))
			break ;
		i++;
		count++;
	}
	return (count);
}

static void	print_args(unsigned int n, char **array)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		printf("%s", array[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
}

int	builtin_echo(int argc, char **argv)
{
	unsigned int	options;

	if (argc < 1 || argv == NULL)
		return (EXIT_FAILURE);
	options = count_option(argc, argv);
	print_args(argc - options - 1, argv + options + 1);
	if (options == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
