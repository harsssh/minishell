/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:50:10 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/30 01:51:29 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <unistd.h>

void	display_exit_message(t_context *ctx)
{
	if (ctx->is_interactive)
	{
		if (ctx->is_login)
			ft_putendl_fd("logout", STDERR_FILENO);
		else
			ft_putendl_fd("exit", STDERR_FILENO);
	}
}
