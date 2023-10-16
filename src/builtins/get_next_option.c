/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 05:33:57 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 13:55:23 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_internal.h"
#include "libft.h"
#include <stddef.h>

static t_getopt_status	set_address_and_return(const char **ptr,
	const char *address, t_getopt_status status)
{
	*ptr = address;
	return (status);
}

void	init_get_next_option(void)
{
	get_next_option(NULL, NULL, NULL);
}

// If `arg` and `valid_options` are NULL,
// initialize the static variable and return 0.
t_getopt_status	get_next_option(const char *arg,
	const char *valid_options, char *option)
{
	static const char	*cur_ptr;
	char				*tmp;

	if (arg == NULL && valid_options == NULL)
		return (set_address_and_return(&cur_ptr, NULL, 0));
	if (cur_ptr == NULL)
	{
		if (arg == NULL || *arg != '-' || arg[1] == '\0')
			return (OPT_END_OF_OPTIONS);
		if (ft_strcmp(arg, "--") == 0)
			return (set_address_and_return(&cur_ptr, NULL, OPT_END_OF_ARG));
		cur_ptr = arg + 1;
	}
	if (*cur_ptr == '\0')
		return (set_address_and_return(&cur_ptr, NULL, OPT_END_OF_ARG));
	tmp = ft_strchr(valid_options, *cur_ptr++);
	if (tmp == NULL)
		return (OPT_ILLEGAL);
	*option = *tmp;
	return (OPT_SUCCESS);
}
