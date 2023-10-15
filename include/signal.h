/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:14:41 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/15 19:15:33 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <sys/signal.h>

extern volatile sig_atomic_t	g_sig;

// sig_handler.c
void	set_sig_global_variable(int sig);

// set_sig_handlers.c
void	set_shell_input_sig_handlers(void);
void	set_shell_exec_sig_handlers(void);
void	set_child_exec_sig_handlers(void);

#endif
