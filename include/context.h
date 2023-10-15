/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:44:52 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 19:12:52 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "ft_list.h"
# include <stdbool.h>

typedef struct s_context
{
	const char	*shell_name;
	t_list		*variables;
	int			last_exit_status;
	char		*cwd;
	bool		is_interactive;
	bool		is_login;
}				t_context;

#endif
