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

# include "variable.h"

char		*make_envstr(char *name, char *value);
t_variable	*variable_create(char *name, char *value);

#endif
