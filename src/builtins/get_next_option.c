/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 05:33:57 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/20 01:04:05 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_internal.h"
#include "libft.h"
#include <stddef.h>

void	init_get_next_option(void)
{
	get_next_option(NULL, NULL);
}

// In a special case where both arguments are NULL,
// initialize the static variable and return 0
t_get_opt_status	get_next_option(char *arg, const char *optstring)
{
	static char	*current_char;
	char		*option;

	if (arg == NULL && optstring == NULL)
	{
		current_char = NULL;
		return (INITIALIZE);
	}
	if (current_char == NULL)
	{
		if (arg == NULL || *arg != '-' || ft_strcmp(arg, "--") == 0)
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
