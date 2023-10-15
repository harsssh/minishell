/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:14:41 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/15 21:46:47 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>

extern volatile sig_atomic_t	g_sig;

void	set_shell_input_sig_handlers(void);
void	set_shell_exec_sig_handlers(void);
void	set_child_exec_sig_handlers(void);

#endif
