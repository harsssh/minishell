/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:23 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/23 04:44:54 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_INTERNAL_H
# define BUILTINS_INTERNAL_H

# include "context.h"
# include "utils.h"

# define ERR_TOO_MANY_ARG	"too many arguments"
# define ERR_NUM_REQUIRED	"numeric argument required"
# define ERR_WRITE			"write error"
# define ERR_NOT_IMPL		"not implemented"
# define ERR_STDOUT			"stdout"
# define ERR_IDENTIFIER		"not a valid identifier"

typedef enum e_get_opt_status
{
	END_OF_ARG,
	END_OF_OPTIONS,
	ILLEGAL_OPTION,
	INITIALIZE,
}					t_get_opt_status;

void				init_get_next_option(void);
t_get_opt_status	get_next_option(const char *arg, const char *optstring);
const char			**ignore_options(const char **args);
char				*get_working_directory(t_context *ctx, char *for_whom);
void				sync_working_directory(t_context *ctx, char *for_whom);

#endif
