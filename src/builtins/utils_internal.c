/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:53:17 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/23 04:45:40 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_internal.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char	**ignore_options(const char **args)
{
	t_getopt_status	status;
	char			c;

	init_get_next_option();
	while (*args)
	{
		status = get_next_option(*args, "", &c);
		if (status == OPT_END_OF_OPTIONS)
			break ;
		if (status == OPT_END_OF_ARG)
			++args;
	}
	return (args);
}
