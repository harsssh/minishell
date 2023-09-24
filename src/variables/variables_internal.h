/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:52 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/23 04:43:58 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_INTERNAL_H
# define VARIABLES_INTERNAL_H

# include "variables.h"

// constructor.c
t_variable	*variable_create(const char *name, const char *value);
void		*variable_copy(void *data);

// utils.internal.c
char		*make_envstr(const char *name, const char *value);
void		variable_destroy(void *data);
int			add_new_variable(t_context *ctx, const char *name,
				const char *value);
int			update_variable(t_variable *var, const char *value);
bool		is_valid_identifier(const char *identifier);

#endif
