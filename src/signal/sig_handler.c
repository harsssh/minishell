/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:15:54 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/15 19:15:55 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

volatile sig_atomic_t	g_sig;

void	set_sig_global_variable(int sig)
{
	g_sig = sig;
}
