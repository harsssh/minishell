/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 05:33:57 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/17 06:14:24 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"
#include "libft.h"
#include <stddef.h>

void	reset_get_next_option(void)
{
	get_next_option(NULL, NULL);
}

int	get_next_option(char *arg, const char *optstring)
{
	static char	*current_char = NULL;
	char		*option;

	if (arg == NULL || optstring == NULL)
	{
		current_char = NULL;
		return (0);
	}
	if (current_char == NULL)
	{
		if (*arg != '-'
			|| ft_strcmp(arg, "-") == 0 || ft_strcmp(arg, "--") == 0)
			return (END_OF_OPTIONS);
		current_char = arg + 1;
	}
	if (*current_char == '\0')
	{
		current_char = NULL;
		return (END_OF_ARG);
	}
	option = ft_strchr(optstring, *current_char++);
	if (option == NULL)
		return (ILLEGAL_OPTION);
	return (*option);
}
