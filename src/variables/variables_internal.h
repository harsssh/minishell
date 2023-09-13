/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:52 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 19:13:48 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_INTERNAL_H
# define VARIABLES_INTERNAL_H

# include "variables.h"

// constructor.c
t_variable	*variable_create(char *name, char *value);
void        *variable_copy(void *data);

// utils.internal.c
void		variable_destroy(void *data);
int			add_new_variable(t_context *ctx, char *name, char *value);
int			update_variable(t_variable *var, char *value);
bool		is_valid_identifier(const char *identifier);

#endif
