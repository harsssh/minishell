/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:06:59 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/30 01:07:28 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "sig.h"

void	init_loop(t_context *ctx)
{
	set_shell_input_sig_handlers();
	if (g_sig != 0)
	{
		ctx->last_exit_status = g_sig + 128;
		g_sig = 0;
	}
}
