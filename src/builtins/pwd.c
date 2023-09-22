/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:34:42 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/19 02:34:44 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins_internal.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	builtins_pwd(t_context *ctx, const char **argv)
{
	char	*directory;

	(void)argv;
	directory = get_working_directory(ctx, "pwd");
	if (directory == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd(directory, STDOUT_FILENO);
	free(directory);
	return (EXIT_SUCCESS);
}
