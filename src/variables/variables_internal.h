/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:52 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 19:14:53 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_INTERNAL_H
# define VARIABLE_INTERNAL_H

# include "variables.h"

t_variable	*variable_create(char *name, char *value);
void		variable_destroy(void *data);
int			add_new_variable(t_context *ctx, char *name, char *value);
int			update_variable(t_variable *var, char *value);
bool		is_valid_identifier(const char *identifier);

#endif
