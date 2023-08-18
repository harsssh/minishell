/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:32:03 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/15 19:58:46 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_H
# define VARIABLE_H

# include "context.h"

# define VAR_ATTR_EXPORTED 1 << 0
# define VAR_ATTR_NO_VALUE 1 << 1

typedef struct s_variable
{
	char	*name;
	char	*value;
	char	*envstr;
	int		attributes;
}			t_variable;

t_variable	*getvar(t_context *ctx, char *name);
int			setvar(t_context *ctx, char *name, char *value, int overwrite);
int 		setvar_from_str(t_context *ctx, char *str, int overwrite);
int			unsetvar(t_context *ctx, char *name);

#endif
