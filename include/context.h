/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:44:52 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 19:14:11 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "ft_list.h"

typedef struct s_context
{
	const char	*shell_name;
	t_list		*variables;
	int			last_exit_status;
	char		*cwd;
}				t_context;

#endif
